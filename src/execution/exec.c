/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/07 14:14:28 by lomartin         ###   ########.fr       */
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

/* int	ft_run_cmds(t_list *commands, t_shell_data *d)
{
	int			fd_in;
	t_command	*cmd;

	fd_in = STDIN_FILENO;
	while (commands)
	{
		cmd = commands->content;
		if (cmd->fdin != STDIN_FILENO)
		{
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			fd_in = cmd->fdin;
		}
		fd_in = ft_run_cmd(fd_in, cmd, d, commands->next);
		commands = commands->next;
	}
	while (wait(NULL) > 0)
		;
	return (fd_in);
} */

int	ft_run_forked_builtin(int (*builtin)(char **a, t_shell_data *d, int in, int out),
		t_run_pipeline_data *rp_d, t_shell_data *data, void *next)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		ft_exit(ft_run_builtin(builtin, rp_d, data, next));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
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
		data.cmd = ft_calloc_gc_id(1, sizeof(t_command), malloc_id_exec);
		data.cmd->fork = data.pipeline;
		data.cmd->args = ft_lsttostrs(ft_parse_cmd(&command_tree->commands, d));
		data.cmd->fdin = ft_parse_fdin(command_tree->commands, d);
		data.cmd->fdout = ft_parse_fdout(command_tree->commands, d);
		if (data.cmd->fdin < 0 || data.cmd->fdout < 0)
			data.cmd->args[0] = "FAILED_OPEN";
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

	if (!command_tree->commands)
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
