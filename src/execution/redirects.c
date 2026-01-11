/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 09:01:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 16:44:50 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_try_replace_fd(int old, char *filename, t_token_op_type type)
{
	int	fd;

	if (type == op_in_redirect)
		fd = open(filename, O_RDONLY);
	if (type == op_out_redirect_append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (type == op_out_redirect_trunc)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (old > 2 && type == op_in_redirect)
		ft_consume_fdin(old);
	else if (old > 2)
		close(old);
	return (fd);
}

static int	ft_open_file(t_open_data *o_d, t_shell_data *d,
		t_run_pipeline_data *runp_data)
{
	o_d->args_lst = ft_parse_cmd_args(o_d->op_token->word, d);
	if (o_d->args_lst->next)
	{
		ft_lstclear_gc(&o_d->args_lst, ft_free);
		return (-2);
	}
	if (o_d->op_token->type == op_in_redirect)
		runp_data->cmd->fdin = ft_try_replace_fd(runp_data->cmd->fdin,
				o_d->args_lst->content, op_in_redirect);
	if (o_d->op_token->type == op_heredoc)
		runp_data->cmd->fdin = ft_open_heredoc(o_d->op_token, d,
				runp_data->cmd->fdin);
	else if (o_d->op_token->type == op_out_redirect_trunc)
		runp_data->cmd->fdout = ft_try_replace_fd(runp_data->cmd->fdout,
				o_d->args_lst->content, op_out_redirect_trunc);
	else if (o_d->op_token->type == op_out_redirect_append)
		runp_data->cmd->fdout = ft_try_replace_fd(runp_data->cmd->fdout,
				o_d->args_lst->content, op_out_redirect_append);
	ft_lstclear_gc(&o_d->args_lst, ft_free);
	return (0);
}

int	ft_parse_fd(t_list *nodes, t_shell_data *d, t_run_pipeline_data *runp_data)
{
	t_open_data	o_d;

	runp_data->cmd->fdin = runp_data->fd_in;
	runp_data->cmd->fdout = STDOUT_FILENO;
	while (nodes)
	{
		o_d.token = nodes->content;
		if (o_d.token->type == token_op)
		{
			o_d.op_token = o_d.token->data;
			if (o_d.op_token->type == op_pipe)
				break ;
			if (ft_open_file(&o_d, d, runp_data) == -2)
				return (ft_parsefd_err(o_d.op_token->word->str, d->progname,
						runp_data, error_expand));
			if (runp_data->cmd->fdin < 0 || runp_data->cmd->fdout < 0)
				return (ft_parsefd_err(o_d.op_token->word->str, d->progname,
						runp_data, error_open));
		}
		nodes = nodes->next;
	}
	return (0);
}
