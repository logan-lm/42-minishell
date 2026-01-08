/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/08 17:04:18 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"

int	ft_run_builtin(int (*builtin)(char **a, t_shell_data *d, int in, int out),
		t_run_pipeline_data *rp_d, t_shell_data *data, void *next)
{
	int	fdout;
	int	exit_status;
	int	pipefd[2];

	fdout = rp_d->cmd->fdout;
	pipe(pipefd);
	if (next && fdout == STDOUT_FILENO)
		fdout = pipefd[1];
	else
		close(pipefd[1]);
	if (builtin == ft_shell_exit)
		close(pipefd[0]);
	exit_status = builtin(rp_d->cmd->args, data, rp_d->fd_in, fdout);
	rp_d->ret = exit_status;
	if (pipefd[1] != STDOUT_FILENO && pipefd[1] != STDIN_FILENO)
		close(pipefd[1]);
	if (!next)
	{
		close(pipefd[0]);
		return (exit_status);
	}
	return (pipefd[0]);
}

int	ft_run_forked_builtin(int (*builtin)(char **a, t_shell_data *d, int in,
			int out), t_run_pipeline_data *rp_d, t_shell_data *data, void *next)
{
	int	fdout;
	int	pipefd[2];
	int	status;
	int	pid;

	fdout = rp_d->cmd->fdout;
	pipe(pipefd);
	if (next && fdout == STDOUT_FILENO)
		fdout = pipefd[1];
	else
		close(pipefd[1]);
	if (builtin == ft_shell_exit)
		close(pipefd[0]);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		ft_exit(builtin(rp_d->cmd->args, data, rp_d->fd_in, fdout));
	}
	if (pipefd[1] != STDOUT_FILENO && pipefd[1] != STDIN_FILENO)
		close(pipefd[1]);
	if (!next)
	{
		close(pipefd[0]);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (pipefd[0]);
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
			if (compounds->is_name)
				setter = 1;
			else if (setter && !compounds->is_name)
				return (nodes_cpy);
			else
				return (nodes);
		}
		else
			return (nodes);
		nodes_cpy = nodes_cpy->next;
	}
	return (nodes);
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
				ft_set_var((char *[2]){ft_expand_compound(compounds, data), NULL}, data, 0, 1);
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
	ft_parse_heredocs(command_tree->commands, d);
	if (g_sig == SIGINT)
		return (130);
	while (command_tree->commands)
	{
		data.has_pipe = ft_has_pipe(command_tree->commands);
		command_tree->commands = ft_assign_vars(command_tree->commands, d);
		data.cmd = ft_calloc_gc_id(1, sizeof(t_command), malloc_id_exec);
		data.cmd->fork = data.pipeline;
		data.ret = ft_parse_fd(command_tree->commands, d, &data);
		data.cmd->args = ft_lsttostrs(ft_parse_cmd(&command_tree->commands, d));
		if (!*data.cmd->args)
		{
			command_tree->commands = ft_next_cmd(command_tree->commands);
			continue ;
		}
		if (data.cmd->fdin < 0 || data.cmd->fdout < 0)
		{
			data.ret = 1;
			data.cmd->args[0] = "FAILED_OPEN";
		}
		if (data.cmd->fdin != STDIN_FILENO)
		{
			if (data.fd_in != STDIN_FILENO)
				close(data.fd_in);
			data.fd_in = data.cmd->fdin;
		}
		data.fd_in = ft_run_cmd(&data, d, ft_next_cmd(command_tree->commands));
		if (!ft_next_cmd(command_tree->commands))
			break ;
		data.has_pipe = ft_has_pipe(command_tree->commands);
		if (data.has_pipe)
			command_tree->commands = ft_next_cmd(command_tree->commands);
	}
	ft_dictadd(&d->vars, "?", ft_itoa_gc(data.ret));
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
