/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 09:01:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 17:06:17 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_open_heredoc(char *limiter, t_shell_data *data)
{
	t_hd_data	hd_data;

	ft_bzero(&hd_data, sizeof(hd_data));
	hd_data.filename = ft_itoa_gc((long)limiter);
	hd_data.temp_w = open(hd_data.filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	hd_data.temp_r = open(hd_data.filename, O_RDONLY);
	unlink(hd_data.filename);
	if (hd_data.temp_r == -1 || hd_data.temp_w == -1)
		return (1);
	while (!ft_is_limiter(hd_data.line, limiter) && g_sig != SIGINT)
	{
		ft_free(hd_data.line);
		hd_data.buffer = readline("> ");
		hd_data.line = ft_strjoin_gc(hd_data.buffer, "\n");
		free(hd_data.buffer);
		if (!hd_data.buffer)
			return (ft_heredoc_eof_err(data, limiter, hd_data.temp_w,
					hd_data.temp_r));
		if (ft_is_limiter(hd_data.line, limiter))
			break ;
		write(hd_data.temp_w, hd_data.line, ft_strlen(hd_data.line));
	}
	close(hd_data.temp_w);
	ft_free(hd_data.line);
	return (hd_data.temp_r);
}

int	ft_fork_heredoc(char *limiter, t_shell_data *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		ft_exit(ft_open_heredoc(limiter, data));
	waitpid(pid, &status, WNOHANG);
	while (g_sig == 0 && !WIFEXITED(status))
	{
		waitpid(pid, &status, WNOHANG);
	}
	return(WEXITSTATUS(status));
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
		o_d->fd = open(o_d->args_lst->content, O_RDONLY);
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
			if (o_d.op_token->type == op_heredoc)
				o_d.fd = ft_open_heredoc(o_d.op_token->word->str, d);
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
