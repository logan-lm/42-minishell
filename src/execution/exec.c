/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 18:01:59 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"

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

t_list	*ft_assign_vars(t_list *nodes, t_shell_data *data,
		t_assign_vars_data a_d)
{
	a_d.nodes_cpy = ft_ignore_varsets(nodes);
	while (a_d.nodes_cpy)
	{
		a_d.token = a_d.nodes_cpy->content;
		if (a_d.token->type == token_op)
		{
			a_d.op_token = a_d.token->data;
			if (a_d.op_token->type == op_pipe)
				return (a_d.nodes_cpy);
		}
		if (a_d.token->type == token_word)
		{
			a_d.compounds = a_d.token->data;
			if (a_d.compounds->is_name)
				ft_set_var((char *[2]){ft_expand_compound(a_d.compounds, data),
					NULL}, data, 0, 1);
			else
				return (a_d.nodes_cpy);
		}
		else
			return (a_d.nodes_cpy);
		a_d.nodes_cpy = a_d.nodes_cpy->next;
	}
	return (a_d.nodes_cpy);
}

void	ft_parse_run_cmds(t_command_node *command_tree, t_shell_data *d,
		t_run_pipeline_data *data)
{
	while (command_tree->commands)
	{
		command_tree->commands = ft_assign_vars(command_tree->commands, d,
				(t_assign_vars_data){0, 0, 0, 0});
		data->cmd = ft_calloc_gc_id(1, sizeof(t_command), malloc_id_exec);
		data->cmd->fork = data->pipeline;
		data->ret = ft_parse_fd(command_tree->commands, d, data);
		data->cmd->args = ft_lsttostrs(ft_parse_cmd(&command_tree->commands,
					d));
		if (!*data->cmd->args)
		{
			if (data->cmd->fdin > 2)
				close(data->cmd->fdin);
			if (data->cmd->fdout > 2)
				close(data->cmd->fdout);
			command_tree->commands = ft_next_cmd(command_tree->commands);
			continue ;
		}
		data->fd_in = ft_run_cmd(data, d, ft_next_cmd(command_tree->commands));
		if (!ft_next_cmd(command_tree->commands))
			break ;
		data->has_pipe = ft_has_pipe(command_tree->commands);
		if (data->has_pipe)
			command_tree->commands = ft_next_cmd(command_tree->commands);
	}
}

int	ft_run_pipeline(t_command_node *command_tree, t_shell_data *d)
{
	t_run_pipeline_data	data;

	ft_bzero(&data, sizeof(t_run_pipeline_data));
	data.pipeline = ft_has_pipe(command_tree->commands);
	if (ft_parse_heredocs(command_tree->commands, d) && g_sig != 130)
		return (1);
	if (g_sig == 130)
		return (130);
	ft_parse_run_cmds(command_tree, d, &data);
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
	if (d->interactive)
	{
		sigaction(SIGINT, &d->sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	return (exit_status);
}
