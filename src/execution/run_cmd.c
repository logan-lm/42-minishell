/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:12:48 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/08 15:39:06 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	ft_run_cmd_child(t_command *cmd, t_shell_data *data, int fdin,
		t_runcmd_data *r_d)
{
	if (r_d->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(r_d->pipefd[0]);
		dup2(r_d->pipefd[1], 1);
		dup2(fdin, 0);
		execve(r_d->cmdpath, cmd->args, ft_str_env(data->envp));
		ft_print_perror(cmd->args[0], data->progname);
		if (errno == 13)
			ft_exit(126);
		ft_exit(127);
	}
}

int	ft_run_cmd_parent(int fdin, void *next, t_shell_data *data,
		t_runcmd_data *r_d)
{
	ft_setpid(r_d->pid);
	if (fdin != STDIN_FILENO && fdin != STDOUT_FILENO)
		close(fdin);
	if (r_d->pipefd[1] != STDOUT_FILENO)
		close(r_d->pipefd[1]);
	if (!next)
	{
		close(r_d->pipefd[0]);
		waitpid(r_d->pid, &data->exit_status, 0);
		if (WIFSIGNALED(data->exit_status))
		{
			ft_sig_handler(WTERMSIG(data->exit_status));
			return (128 + WTERMSIG(data->exit_status));
		}
		return (WEXITSTATUS(data->exit_status));
	}
	return (r_d->pipefd[0]);
}

int	ft_run_cmd(t_run_pipeline_data *rp_d, t_shell_data *data, void *next)
{
	t_runcmd_data	r_d;

	if (!*rp_d->cmd->args[0])
		return (0);
	r_d.cmdpath = ft_get_builtin(rp_d->cmd->args[0]);
	if (r_d.cmdpath && !rp_d->cmd->fork)
		return (ft_run_builtin(r_d.cmdpath, rp_d, data, next));
	else if (r_d.cmdpath && rp_d->cmd->fork)
		return (ft_run_forked_builtin(r_d.cmdpath, rp_d, data, next));
	if (ft_strncmp(rp_d->cmd->args[0], "FAILED_OPEN", 12))
		r_d.cmdpath = ft_get_cmdpath(rp_d->cmd->args[0], data->envp, &rp_d->ret, data->progname);
	pipe(r_d.pipefd);
	if ((!next || rp_d->cmd->fdout != STDOUT_FILENO) && !close(r_d.pipefd[1]))
		r_d.pipefd[1] = rp_d->cmd->fdout;
	if (!ft_strncmp(rp_d->cmd->args[0], "FAILED_OPEN", 12) || !r_d.cmdpath)
	{
		if (!rp_d->ret)
			rp_d->ret = 1;
		if (r_d.pipefd[1] != STDOUT_FILENO)
			close(r_d.pipefd[1]);
		if (!next)
			close(r_d.pipefd[0]);
		return (r_d.pipefd[0]);
	}
	signal(SIGINT, SIG_IGN);
	r_d.pid = fork();
	ft_run_cmd_child(rp_d->cmd, data, rp_d->fd_in, &r_d);
	return (ft_run_cmd_parent(rp_d->fd_in, next, data, &r_d));
}
