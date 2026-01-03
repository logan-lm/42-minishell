/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/02 20:16:06 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"

int	ft_run_builtin(int(builtin)(char **a, t_shell_data *d, int in, int out),
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

int	ft_run_cmd(int fdin, t_command *cmd, t_shell_data *data, void *next)
{
	int		pid;
	int		pipefd[2];
	void	*cmdpath;

	cmdpath = ft_get_builtin(cmd->args[0]);
	if (cmdpath)
		return (ft_run_builtin(cmdpath, cmd, data, next, fdin));
	if (ft_strncmp(cmd->args[0], "FAILED_OPEN", 12))
		cmdpath = ft_get_cmdpath(cmd->args[0], data->envp);
	pipe(pipefd);
	if ((!next || cmd->fdout != STDOUT_FILENO) && !close(pipefd[1]))
		pipefd[1] = cmd->fdout;
	if (!ft_strncmp(cmd->args[0], "FAILED_OPEN", 12) || !cmdpath)
	{
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		dup2(fdin, 0);
		execve(cmdpath, cmd->args, ft_str_env(data->envp));
		ft_print_perror(cmd->args[0], data->progname);
		exit(127);
	}
	if (fdin != STDIN_FILENO && fdin != STDOUT_FILENO)
		close(fdin);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
	if (!next)
	{
		close(pipefd[0]);
		waitpid(pid, &data->exit_status, 0);
		return (WEXITSTATUS(data->exit_status));
	}
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
		exit (ft_run_cmds(commands, d));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_is_only_varset(t_list *commands)
{
	t_command	*cmd;

	while (commands)
	{
		cmd = commands->content;
		if (!ft_is_varset(*(cmd->args)))
			return (0);
		commands = commands->next;
	}
	return (1);
}

int	ft_run_pipeline(t_command_node *command_tree, t_shell_data *d)
{
	int			has_pipe;
	t_list		*commands;
	t_command	*cmd;

	commands = NULL;
	has_pipe = 0;
	while (command_tree->commands)
	{
		cmd = ft_calloc_gc(1, sizeof(t_command));
		cmd->args = ft_lsttostrs(ft_parse_cmd(&command_tree->commands, d));
		//cmd->args = ft_lsttostrs(ft_check_wildcards(tmp_args));
		cmd->fdin = ft_parse_fdin(command_tree->commands, d);
		cmd->fdout = ft_parse_fdout(command_tree->commands, d);
		if (cmd->fdin < 0 || cmd->fdout < 0)
			cmd->args[0] = "FAILED_OPEN";
		ft_lstadd_back(&commands, ft_lstnew_gc(cmd));
		if (!ft_next_cmd(command_tree->commands))
			break ;
		has_pipe = ft_has_pipe(command_tree->commands);
		if (has_pipe)
			command_tree->commands = ft_next_cmd(command_tree->commands);
	}
	if (has_pipe && !ft_is_only_varset(commands))
		return (ft_forked_run(commands, d));
	return (ft_run_cmds(commands, d));
}

int	ft_exec(t_command_node *command_tree, t_shell_data *d)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
	d->lines++;
	if (command_tree->type == command_pipeline)
		exit_status = ft_run_pipeline(command_tree, d);
	if (command_tree->type == command_and)
		exit_status = ft_and(command_tree, d);
	if (command_tree->type == command_or)
		exit_status = ft_or(command_tree, d);
	while (wait(NULL) > 0)
		;
	return (exit_status);
}
