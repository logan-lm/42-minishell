/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 19:53:09 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"

int	ft_run_builtin(int (*builtin)(char **a, t_shell_data *d, int in, int out),
		t_run_pipeline_data *rp_d, t_runcmd_data *r_d, t_shell_data *data)
{
	int	return_value;
	int	initial_fdin;

	initial_fdin = r_d->fd_in;
	if (rp_d->pipeline)
	{
		r_d->fd_in = STDIN_FILENO;
		r_d->fd_out = STDOUT_FILENO;
	}
	return_value = builtin(rp_d->cmd->args, data, r_d->fd_in, r_d->fd_out);
	if (rp_d->pipeline)
	{
		if (initial_fdin > 2)
			ft_consume_fdin(r_d->fd_in);
		else
			close(r_d->fd_in);
		close(r_d->fd_out);
	}
	return (return_value);
}

t_list	*ft_ignore_varsets(t_list *nodes)
{
	t_list					*nodes_cpy;
	t_parsing_token			*token;
	t_string_compound_lst	*compounds;
	int						setter;

	setter = 0;
	nodes_cpy = nodes;
	while (nodes_cpy)
	{
		token = nodes_cpy->content;
		if (token->type == token_word)
		{
			compounds = token->data;
			if (setter && !compounds->is_name)
				return (nodes_cpy);
			if (compounds->is_name && nodes_cpy->next)
				setter = 1;
			else
				return (nodes);
		}
		else
			return (nodes_cpy);
		nodes_cpy = nodes_cpy->next;
	}
	return (nodes_cpy);
}

t_list	*ft_assign_vars(t_list *nodes, t_shell_data *data)
{
	t_list					*nodes_cpy;
	t_parsing_token			*token;
	t_token_op_data			*op_token;
	t_string_compound_lst	*compounds;

	nodes = ft_ignore_varsets(nodes);
	nodes_cpy = nodes;
	while (nodes_cpy)
	{
		token = nodes_cpy->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
				return (nodes_cpy);
		}
		if (token->type == token_word)
		{
			compounds = token->data;
			if (compounds->is_name)
				ft_set_var((char *[2]){ft_expand_compound(compounds, data),
					NULL}, data, 0, 1);
			else
				return (nodes_cpy);
		}
		else
			return (nodes_cpy);
		nodes_cpy = nodes_cpy->next;
	}
	return (nodes_cpy);
}

int	ft_run_pipeline(t_command_node *command_tree, t_shell_data *d)
{
	t_run_pipeline_data	data;

	ft_bzero(&data, sizeof(t_run_pipeline_data));
	data.pipeline = ft_has_pipe(command_tree->commands);
	if (ft_parse_heredocs(command_tree->commands, d) && g_sig != SIGINT)
		return (1);
	if (g_sig == SIGINT)
		return (g_sig = 0, 130);
	while (command_tree->commands)
	{
		command_tree->commands = ft_assign_vars(command_tree->commands, d);
		data.cmd = ft_calloc_gc_id(1, sizeof(t_command), malloc_id_exec);
		data.cmd->fork = data.pipeline;
		data.ret = ft_parse_fd(command_tree->commands, d, &data);
		data.cmd->args = ft_lsttostrs(ft_parse_cmd(&command_tree->commands, d));
		data.fd_in = ft_run_cmd(&data, d, ft_next_cmd(command_tree->commands));
		if (!ft_next_cmd(command_tree->commands))
			break ;
		data.has_pipe = ft_has_pipe(command_tree->commands);
		if (data.has_pipe)
			command_tree->commands = ft_next_cmd(command_tree->commands);
	}
	return (data.ret);
}

int	ft_exec(t_command_node *command_tree, t_shell_data *d)
{
	int	exit_status;
	int	status;

	if (!command_tree)
		return (2);
	exit_status = EXIT_FAILURE;
	d->lines++;
	if (command_tree->type == command_pipeline)
		exit_status = ft_run_pipeline(command_tree, d);
	else if (command_tree->type == command_and)
		exit_status = ft_and(command_tree, d);
	else if (command_tree->type == command_or)
		exit_status = ft_or(command_tree, d);
	while (wait(&status) > 0)
		;
	ft_setpid(0);
	sigaction(SIGINT, &d->sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	return (exit_status);
}
