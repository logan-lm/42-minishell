/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 09:01:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 20:19:18 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

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
				signal(SIGINT, ft_sig_hd_handler);
				o_d.op_token->word->heredoc_fd = ft_o_hdoc(
						o_d.op_token->word->str,
						o_d.op_token->word->heredoc_fd, d);
				sigaction(SIGINT, &d->sa, NULL);
				if (g_sig == SIGINT || o_d.op_token->word->heredoc_fd < 0)
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

char	*ft_read_expand_fd(int fd)
{
	size_t	read_bytes;
	char	buffer[BUFFER_SIZE + 1];
	char	*joined;
	char	*temp;

	joined = NULL;
	read_bytes = 1;
	while (read_bytes)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';
		temp = joined;
		joined = ft_strjoin_gc_id(joined, buffer, malloc_id_exec);
		ft_free(temp);
	}
	close(fd);
	return (joined);
}

int	ft_expand_heredoc(t_token_op_data *op_token, t_shell_data *d)
{
	t_hd_data	hd_data;
	char		*buffer;
	char		*temp;

	ft_bzero(&hd_data, sizeof(t_hd_data));
	buffer = ft_read_expand_fd(op_token->word->heredoc_fd);
	hd_data.temp = ft_ltoa_gc((long)buffer);
	ft_set_tmp_paths(&hd_data, d);
	if (ft_try_open_tmpfile(&hd_data))
		return (-1);
	ft_free(hd_data.temp);
	ft_free(hd_data.filename);
	temp = buffer;
	buffer = ft_expand_word(buffer, d);
	ft_free(temp);
	ft_putstr_fd(buffer, hd_data.temp_w);
	close(hd_data.temp_w);
	ft_free(buffer);
	return (hd_data.temp_r);
}

int	ft_open_heredoc(t_token_op_data *op_token, t_shell_data *d, int oldfd)
{
	int	fd;

	if (!op_token->word->is_naked)
		fd = op_token->word->heredoc_fd;
	else
		fd = ft_expand_heredoc(op_token, d);
	if (oldfd > 2)
		close(oldfd);
	return (fd);
}

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
	else if(old > 2)
		close(old);
	return (fd);
}

static int	ft_open_file(t_open_data *o_d, t_shell_data *d,
		t_run_pipeline_data *runp_data)
{
	/* if ((o_d->op_token->type == op_out_redirect_trunc
			|| o_d->op_token->type == op_out_redirect_append)
		&& runp_data->cmd->fdout != STDOUT_FILENO)
		close(runp_data->cmd->fdout); */
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
