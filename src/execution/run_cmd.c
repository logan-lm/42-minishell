/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:12:48 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/09 21:09:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_close_onerror(t_run_pipeline_data *rp_d, t_runcmd_data *r_d, void *next)
{
	if (!rp_d->ret)
		rp_d->ret = 1;
	if (r_d->pipefd[1] > 2)
		close(r_d->pipefd[1]);
	if (!next && r_d->fd_out > 2)
		close(r_d->fd_out);
	return (r_d->pipefd[0]);
}

void	ft_run_cmd_child(t_command *cmd, t_shell_data *data, t_runcmd_data *r_d)
{
	if (r_d->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(r_d->pipefd[0]);
		dup2(r_d->fd_out, 1);
		if (r_d->fd_in)
			dup2(r_d->fd_in, 0);
		if (r_d->cmd_type == cmd_builtin)
			ft_exit(ft_run_builtin(r_d->cmdpath, cmd->args, r_d, data));
		execve(r_d->cmdpath, cmd->args, ft_str_env(data->envp));
		ft_print_perror(cmd->args[0], data->progname);
		if (errno == 13)
			ft_exit(126);
		ft_exit(127);
	}
}

int	ft_run_cmd_parent(t_run_pipeline_data *rp_d, void *next, t_shell_data *data,
		t_runcmd_data *r_d)
{
	ft_setpid(r_d->pid);
	if (rp_d->fd_in > 2)
		close(r_d->fd_in);
	if (r_d->pipefd[1])
		close(r_d->pipefd[1]);
	if (!next)
	{
		if (r_d->pipefd[0])
			close(r_d->pipefd[0]);
		waitpid(r_d->pid, &data->exit_status, 0);
		if (WIFSIGNALED(data->exit_status))
		{
			ft_sig_handler(WTERMSIG(data->exit_status));
			return (128 + WTERMSIG(data->exit_status));
		}
		rp_d->ret = WEXITSTATUS(data->exit_status);
	}
	return (r_d->pipefd[0]);
}

void	ft_try_get_cmd(t_runcmd_data *r_d, t_run_pipeline_data *rp_d,
		t_shell_data *data)
{
	if (!ft_strncmp(rp_d->cmd->args[0], "FAILED_OPEN", 12))
	{
		r_d->cmd_type = cmd_error;
		return ;
	}
	r_d->cmdpath = ft_get_builtin(rp_d->cmd->args[0]);
	if (r_d->cmdpath)
	{
		r_d->cmd_type = cmd_builtin;
		return ;
	}
	r_d->cmdpath = ft_get_cmdpath(rp_d->cmd->args[0], data->envp, &rp_d->ret,
			data->progname);
	if (r_d->cmdpath)
	{
		r_d->cmd_type = cmd_exec;
		return ;
	}
	r_d->cmd_type = cmd_error;
}

int	ft_run_cmd(t_run_pipeline_data *rp_d, t_shell_data *data, void *next)
{
	t_runcmd_data	r_d;

	ft_bzero(&r_d, sizeof(t_runcmd_data));
	if (!rp_d->cmd->args[0])
		return (0);
	ft_try_get_cmd(&r_d, rp_d, data);
	r_d.fd_in = rp_d->fd_in;
	if ((!next || rp_d->cmd->fdout != STDOUT_FILENO))
		r_d.fd_out = rp_d->cmd->fdout;
	else
	{
		pipe(r_d.pipefd);
		r_d.fd_out = r_d.pipefd[1];
	}
	if (r_d.cmd_type == cmd_error)
		return (ft_close_onerror(rp_d, &r_d, next));
	if (r_d.cmd_type == cmd_builtin && !rp_d->cmd->fork)
		return (ft_run_builtin(r_d.cmdpath, rp_d->cmd->args, &r_d, data));
	signal(SIGINT, SIG_IGN);
	r_d.pid = fork();
	ft_run_cmd_child(rp_d->cmd, data, &r_d);
	return (ft_run_cmd_parent(rp_d, next, data, &r_d));
}
