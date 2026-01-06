/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/06 10:04:25 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"

int	ft_run_builtin(int (*builtin)(char **a, t_shell_data *d, int in, int out),
		t_command *cmd, t_shell_data *data, void *next, int fdin)
{
	int	fdout;
	int	exit_status;
	int	pipefd[2];

	fdout = cmd->fdout;
	pipe(pipefd);
	if (next && fdout == STDOUT_FILENO)
		fdout = pipefd[1];
	else
		close(pipefd[1]);
	exit_status = builtin(cmd->args, data, fdin, fdout);
	if (!next)
		return (exit_status);
	return (pipefd[0]);
}

int	ft_run_cmds(t_list *commands, t_shell_data *d)
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
}

int	ft_forked_run(t_list *commands, t_shell_data *d)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		ft_exit(ft_run_cmds(commands, d));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_run_pipeline(t_command_node *command_tree, t_shell_data *d)
{
	t_run_pipeline_data	data;

	ft_bzero(&data, sizeof(t_run_pipeline_data));
	while (command_tree->commands)
	{
		data.cmd = ft_calloc_gc_id(1, sizeof(t_command), malloc_id_exec);
		ft_parse_heredocs(command_tree->commands, d);
		if (g_sig == SIGINT)
			return (130);
		data.cmd->args = ft_lsttostrs(ft_parse_cmd(&command_tree->commands, d));
		data.cmd->fdin = ft_parse_fdin(command_tree->commands, d);
		data.cmd->fdout = ft_parse_fdout(command_tree->commands, d);
		if (data.cmd->fdin < 0 || data.cmd->fdout < 0)
			data.cmd->args[0] = "FAILED_OPEN";
		ft_lstadd_back(&data.commands, ft_lstnew_gc_id(data.cmd,
				malloc_id_exec));
		if (!ft_next_cmd(command_tree->commands))
			break ;
		data.has_pipe = ft_has_pipe(command_tree->commands);
		if (data.has_pipe)
			command_tree->commands = ft_next_cmd(command_tree->commands);
	}
	if (data.has_pipe && !ft_is_only_varset(data.commands))
		return (ft_forked_run(data.commands, d));
	return (ft_run_cmds(data.commands, d));
}

int	ft_exec(t_command_node *command_tree, t_shell_data *d)
{
	int	exit_status;
	int	status;

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
