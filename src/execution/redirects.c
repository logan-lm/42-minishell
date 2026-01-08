/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 09:01:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/08 12:06:30 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	ft_parse_heredocs(t_list *nodes, t_shell_data *d)
{
	t_open_data			o_d;

	while (nodes)
	{
		o_d.token = nodes->content;
		if (o_d.token && o_d.token->type == token_op)
		{
			o_d.op_token = o_d.token->data;
			if (o_d.op_token->type == op_heredoc
				&& o_d.op_token->word->heredoc_fd == -1)
			{
				signal(SIGINT, ft_sig_hd_handler);
				o_d.op_token->word->heredoc_fd = ft_o_hdoc(o_d.op_token->word->str,
						d);
				sigaction(SIGINT, &d->sa, NULL);
				if (g_sig == SIGINT)
					return ;
			}
		}
		if (o_d.token && o_d.token->type == token_subshell)
			nodes = o_d.token->data;
		nodes = nodes->next;
	}
}

int	ft_expand_heredoc(t_token_op_data *op_token, t_shell_data *d)
{
	size_t		read_bytes;
	t_hd_data	hd_data;
	char		buffer[BUFFER_SIZE + 1];
	char		*joined;
	char		*temp;

	joined = NULL;
	read_bytes = 1;
	ft_bzero(&hd_data, sizeof(hd_data));
	while (read_bytes)
	{
		read_bytes = read(op_token->word->heredoc_fd, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';
		temp = joined;
		joined = ft_strjoin_gc_id(joined, buffer, malloc_id_exec);
		ft_free(temp);
	}
	close(op_token->word->heredoc_fd);
	hd_data.temp = ft_ltoa_gc((long)joined);
	hd_data.filename = ft_strjoin_gc_id("/tmp/heredoc_", hd_data.temp,
			malloc_id_exec);
	ft_free(hd_data.temp);
	hd_data.temp_w = open(hd_data.filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	hd_data.temp_r = open(hd_data.filename, O_RDONLY);
	unlink(hd_data.filename);
	ft_free(hd_data.filename);
	temp = joined;
	joined = ft_expand_word(joined, d);
	ft_free(temp);
	ft_putstr_fd(joined, hd_data.temp_w);
	close(hd_data.temp_w);
	ft_free(joined);
	return (hd_data.temp_r);
}

int	ft_open_heredoc(t_token_op_data *op_token, t_shell_data *d)
{
	if (!op_token->word->is_naked)
		return (op_token->word->heredoc_fd);
	return (ft_expand_heredoc(op_token, d));
}

int	ft_try_replace_fdin(int old, char *filename)
{
	int	fdin;

	fdin = open(filename, O_RDONLY);
	if (old != STDIN_FILENO)
		close(old);
	return (fdin);
}

static int	ft_open_file(t_open_data *o_d, t_shell_data *d)
{
	if ((o_d->op_token->type == op_out_redirect_trunc
			|| o_d->op_token->type == op_out_redirect_append)
		&& o_d->fd != STDOUT_FILENO)
		close(o_d->fd);
	o_d->args_lst = ft_parse_cmd_args(o_d->op_token->word, d);
	if (o_d->args_lst->next)
	{
		ft_lstclear_gc(&o_d->args_lst, ft_free);
		return (-2);
	}
	if (o_d->op_token->type == op_in_redirect)
		o_d->fd = ft_try_replace_fdin(o_d->fd, o_d->args_lst->content);
	if (o_d->op_token->type == op_heredoc)
		o_d->fd = ft_open_heredoc(o_d->op_token, d);
	else if (o_d->op_token->type == op_out_redirect_trunc)
		o_d->fd = open(o_d->args_lst->content, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else if (o_d->op_token->type == op_out_redirect_append)
		o_d->fd = open(o_d->op_token->word->str, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	ft_lstclear_gc(&o_d->args_lst, ft_free);
	return (0);
}

int	ft_parse_fdin(t_list *nodes, t_shell_data *d)
{
	t_open_data	o_d;

	o_d.fd = STDIN_FILENO;
	while (nodes)
	{
		o_d.token = nodes->content;
		if (o_d.token->type == token_op)
		{
			o_d.op_token = o_d.token->data;
			if (o_d.op_token->type == op_pipe)
				break ;
			if (o_d.op_token->type == op_in_redirect
				|| o_d.op_token->type == op_heredoc)
			{
				if (ft_open_file(&o_d, d) == -2)
					return (ft_exp_err(o_d.op_token->word->str, d->progname));
			}
			if (o_d.fd < 0)
				return (ft_open_err(o_d.op_token->word->str, d->progname));
		}
		nodes = nodes->next;
	}
	return (o_d.fd);
}

int	ft_parse_fdout(t_list *nodes, t_shell_data *d)
{
	t_open_data	o_d;

	o_d.fd = STDOUT_FILENO;
	while (nodes)
	{
		o_d.token = nodes->content;
		if (o_d.token->type == token_op)
		{
			o_d.op_token = o_d.token->data;
			if (o_d.op_token->type == op_pipe)
				break ;
			if (o_d.op_token->type == op_out_redirect_trunc)
				if (ft_open_file(&o_d, d) == -2)
					return (ft_exp_err(o_d.op_token->word->str, d->progname));
			if (o_d.op_token->type == op_out_redirect_append)
				if (ft_open_file(&o_d, d) == -2)
					return (ft_exp_err(o_d.op_token->word->str, d->progname));
			if (o_d.fd < 0)
				return (ft_open_err(o_d.op_token->word->str, d->progname));
		}
		nodes = nodes->next;
	}
	return (o_d.fd);
}
