/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:15:09 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 17:39:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	ft_close_onerror(t_run_pipeline_data *rp_d, t_runcmd_data *r_d, void *next)
{
	(void)next;
	if (!rp_d->ret)
		rp_d->ret = 1;
	if (r_d->fd_in > 2)
		close(r_d->fd_in);
	if (r_d->fd_out > 2)
		close(r_d->fd_out);
	if (r_d->pipefd)
	{
		close(r_d->pipefd[1]);
		return (r_d->pipefd[0]);
	}
	return (-1);
}

void	ft_try_get_cmd(t_runcmd_data *r_d, t_run_pipeline_data *rp_d,
		t_shell_data *data)
{
	if (rp_d->cmd->error)
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

void	ft_run_init_fds(t_runcmd_data *r_d, t_run_pipeline_data *rp_d,
		void *next)
{
	r_d->fd_in = rp_d->cmd->fdin;
	if (!next)
		r_d->fd_out = rp_d->cmd->fdout;
	else
	{
		r_d->pipefd = ft_malloc_id(sizeof(int) * 2, malloc_id_exec);
		pipe(r_d->pipefd);
		r_d->fd_out = r_d->pipefd[1];
	}
	if (rp_d->cmd->fdout != STDOUT_FILENO && rp_d->cmd->fdout != r_d->fd_out)
	{
		if (r_d->fd_out > 2)
			close(r_d->fd_out);
		r_d->fd_out = rp_d->cmd->fdout;
	}
}
