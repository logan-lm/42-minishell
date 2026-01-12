/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:12:48 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/12 19:18:46 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

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

void	ft_init_child(t_runcmd_data *r_d, t_shell_data *data)
{
	if (data->interactive)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (r_d->fd_out != STDOUT_FILENO)
	{
		dup2(r_d->fd_out, STDOUT_FILENO);
		close(r_d->fd_out);
	}
	if (r_d->fd_in)
	{
		dup2(r_d->fd_in, STDIN_FILENO);
		close(r_d->fd_in);
	}
	if (r_d->pipefd)
		close(r_d->pipefd[0]);
}

void	ft_run_cmd_child(t_run_pipeline_data *rp_d, t_shell_data *data,
		t_runcmd_data *r_d)
{
	if (r_d->pid == 0)
	{
		ft_init_child(r_d, data);
		if (r_d->cmd_type == cmd_builtin)
			ft_exit(ft_run_builtin(r_d->cmdpath, rp_d, r_d, data));
		execve(r_d->cmdpath, rp_d->cmd->args, ft_str_env(data->envp));
		if (r_d->fd_in > 2)
			close(r_d->fd_in);
		if (r_d->fd_out > 2)
			close(r_d->fd_out);
		ft_print_perror(rp_d->cmd->args[0], data->progname);
		if (errno == 13)
			ft_exit(126);
		ft_exit(127);
	}
}

int	ft_run_cmd_parent(t_run_pipeline_data *rp_d, void *next, t_shell_data *data,
		t_runcmd_data *r_d)
{
	ft_setpid(r_d->pid);
	if (r_d->fd_in > 2)
		close(r_d->fd_in);
	if (r_d->fd_out > 2)
		close(r_d->fd_out);
	if (!next)
	{
		waitpid(r_d->pid, &data->exit_status, 0);
		if (r_d->pipefd)
			close(r_d->pipefd[0]);
		if (WIFSIGNALED(data->exit_status))
		{
			ft_sig_handler(WTERMSIG(data->exit_status));
			rp_d->ret = 128 + WTERMSIG(data->exit_status);
			return (128 + WTERMSIG(data->exit_status));
		}
		rp_d->ret = WEXITSTATUS(data->exit_status);
	}
	if (r_d->pipefd)
		return (r_d->pipefd[0]);
	return (-1);
}

int	ft_run_cmd(t_run_pipeline_data *rp_d, t_shell_data *data, void *next)
{
	t_runcmd_data	r_d;

	data->wc_path = NULL;
	ft_bzero(&r_d, sizeof(t_runcmd_data));
	if (!rp_d->cmd->args[0])
		return (0);
	ft_try_get_cmd(&r_d, rp_d, data);
	ft_run_init_fds(&r_d, rp_d, next);
	if (r_d.cmd_type == cmd_error)
		return (ft_close_onerror(rp_d, &r_d, next));
	if (r_d.cmd_type == cmd_builtin && !rp_d->cmd->fork)
	{
		rp_d->ret = ft_run_builtin(r_d.cmdpath, rp_d, &r_d, data);
		return (0);
	}
	if (data->interactive)
		signal(SIGINT, SIG_IGN);
	r_d.pid = fork();
	ft_run_cmd_child(rp_d, data, &r_d);
	return (ft_run_cmd_parent(rp_d, next, data, &r_d));
}
