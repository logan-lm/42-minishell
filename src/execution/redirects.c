/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 09:01:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/06 11:02:52 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_heredoc_handler(void)
{
	if (g_sig == SIGINT)
		rl_done = 1;
	return (0);
}

void	ft_sig_hd_handler(int sig)
{
	g_sig = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char	*ft_open_heredoc(char *limiter, t_shell_data *data)
{
	t_hd_data	hd_data;

	ft_bzero(&hd_data, sizeof(hd_data));
	hd_data.temp = ft_ltoa_gc((long)limiter);
	hd_data.filename = ft_strjoin_gc_id("/tmp/heredoc_", hd_data.temp,
			malloc_id_exec);
	ft_free(hd_data.temp);
	hd_data.temp_w = open(hd_data.filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (hd_data.temp_w == -1)
		return (ft_strdup_gc_id("FAILED_OPEN", malloc_id_exec));
	rl_event_hook = ft_heredoc_handler;
	while (!ft_is_limiter(hd_data.line, limiter) && g_sig != SIGINT)
	{
		ft_free(hd_data.line);
		hd_data.buffer = readline("> ");
		hd_data.line = ft_strjoin_gc_id(hd_data.buffer, "\n", malloc_id_exec);
		free(hd_data.buffer);
		if (!hd_data.buffer)
			return (ft_heredoc_eof_err(data, limiter, hd_data.temp_w,
					hd_data.filename));
		if (ft_is_limiter(hd_data.line, limiter))
			break ;
		write(hd_data.temp_w, hd_data.line, ft_strlen(hd_data.line));
	}
	close(hd_data.temp_w);
	ft_free(hd_data.line);
	return (hd_data.filename);
}

void	ft_parse_heredocs(t_list *nodes, t_shell_data *d)
{
	t_open_data	o_d;

	while (nodes)
	{
		o_d.token = nodes->content;
		if (o_d.token && o_d.token->type == token_op)
		{
			o_d.op_token = o_d.token->data;
			if (o_d.op_token->type == op_heredoc)
			{
				signal(SIGINT, ft_sig_hd_handler);
				o_d.op_token->word->str = ft_open_heredoc(o_d.op_token->word->str,
						d);
				signal(SIGINT, ft_sig_handler);
				if (g_sig == SIGINT)
				{
					ft_free(o_d.op_token->word->str);
					return ;
				}
				o_d.op_token->type = op_in_redirect;
			}
		}
		if (o_d.token && o_d.token->type == token_subshell)
			nodes = o_d.token->data;
		nodes = nodes->next;
	}
}

/* int	ft_open_heredoc(int fd, int filename)
{
	size_t		i;
	char		*line;
	char		*temp;
	t_hd_data	hd_data;

	i = 0;
	line = get_next_line_count_gc(fd, &i);
	while (i)
	{
		temp = line;
		line = ft_strjoin_gc_id(temp, get_next_line_count_gc(fd, &i),
				malloc_id_exec);
		free(temp);
	}
	close(fd);
	unlink(filename);
	hd_data.temp_w = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	hd_data.temp_r = open(filename, O_RDONLY);
	while (line[i])
	{
		if (line[i] == '$' && (!*(word + 1) || (ft_isalpha(*(word + 1))
					|| *(word + 1) == '?')))
	}
} */
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
	{
		o_d->fd = open(o_d->args_lst->content, O_RDONLY);
		if (ft_strncmp("/tmp/heredoc_", o_d->args_lst->content, 13))
			unlink(o_d->args_lst->content);
	}
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
			if (o_d.op_token->type == op_in_redirect)
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
