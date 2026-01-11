/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:23:50 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 16:44:12 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	ft_heredoc_mode(t_open_data *o_d, t_shell_data *d)
{
	if (d->interactive)
		signal(SIGINT, ft_sig_hd_handler);
	o_d->op_token->word->heredoc_fd = ft_o_hdoc(
			o_d->op_token->word->str,
			o_d->op_token->word->heredoc_fd, d);
	if (d->interactive)
		sigaction(SIGINT, &d->sa, NULL);
}

int	ft_parse_heredocs(t_list *nodes, t_shell_data *d)
{
	t_open_data	o_d;

	while (nodes)
	{
		o_d.token = nodes->content;
		if (o_d.token && o_d.token->type == token_op)
		{
			o_d.op_token = o_d.token->data;
			if (o_d.op_token->type == op_heredoc
				&& o_d.op_token->word->heredoc_fd == -1)
			{
				ft_heredoc_mode(&o_d, d);
				if (g_sig == 130 || o_d.op_token->word->heredoc_fd < 0)
				{
					if (o_d.op_token->word->heredoc_fd > 2)
						close(o_d.op_token->word->heredoc_fd);
					return (1);
				}
			}
		}
		if (o_d.token && o_d.token->type == token_subshell)
			nodes = o_d.token->data;
		nodes = nodes->next;
	}
	return (0);
}

int	ft_o_hdoc_while(char *limiter, t_hd_data *hd_data, t_shell_data *d)
{
	while (!ft_is_limiter(hd_data->line, limiter) && g_sig != 130)
	{
		ft_free(hd_data->line);
		if (d->interactive)
			hd_data->buffer = readline("> ");
		else
			hd_data->buffer = get_next_line(0);
		if (!hd_data->buffer)
		{
			ft_sethd(1);
			close(hd_data->temp_w);
			return (1);
		}
		hd_data->line = ft_strjoin_gc_id(hd_data->buffer, "\n", malloc_id_exec);
		free(hd_data->buffer);
		if (ft_is_limiter(hd_data->line, limiter))
			break ;
		write(hd_data->temp_w, hd_data->line, ft_strlen(hd_data->line));
	}
	return (0);
}

int	ft_o_hdoc(char *limiter, int oldfd, t_shell_data *data)
{
	t_hd_data	hd_data;
	int			ret;

	if (oldfd > 2)
		close(oldfd);
	ft_bzero(&hd_data, sizeof(hd_data));
	hd_data.temp = ft_ltoa_gc((long)limiter);
	ft_set_tmp_paths(&hd_data, data);
	if (ft_try_open_tmpfile(&hd_data))
		return (-1);
	ft_free(hd_data.temp);
	ft_lstadd_front(&data->opened_hd, ft_lstnew_gc_id(hd_data.filename,
			malloc_id_exec));
	ft_setfd(hd_data.temp_w);
	rl_event_hook = ft_heredoc_handler;
	ret = ft_o_hdoc_while(limiter, &hd_data, data);
	rl_event_hook = NULL;
	close(hd_data.temp_w);
	ft_free(hd_data.filename);
	if (ret)
		return (ft_heredoc_eof_err(data, limiter, hd_data.temp_r));
	ft_free(hd_data.line);
	return (hd_data.temp_r);
}
