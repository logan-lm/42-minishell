/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 09:01:37 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/01 18:17:37 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_open_heredoc(char *limiter, t_shell_data *data)
{
	char	*filename;
	int		temp_w;
	int		temp_r;
	char	*buffer;
	char	*line;

	filename = ft_itoa_gc((long)limiter);
	temp_w = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	temp_r = open(filename, O_RDONLY);
	unlink(filename);
	buffer = NULL;
	if (temp_r == -1 || temp_w == -1)
		return (1);
	while (!ft_is_limiter(line, limiter))
	{
		ft_free(line);
		buffer = readline("> ");
		line = ft_strjoin_gc(buffer, "\n");
		free(buffer);
		if (!buffer)
			return (ft_heredoc_eof_err(data, limiter, temp_w, temp_r));
		if (ft_is_limiter(line, limiter))
			break ;
		write(temp_w, line, ft_strlen(line));
	}
	close(temp_w);
	ft_free(line);
	return (temp_r);
}

int	ft_parse_fdin(t_list *nodes, t_shell_data *d)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;
	t_list			*args_lst;
	int				fd;

	fd = STDIN_FILENO;
	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
				break ;
			if (op_token->type == op_in_redirect)
			{
				args_lst = ft_parse_cmd_args(op_token->word, d);
				if (ft_str_hasspace(args_lst->content)
					|| ft_strhasc(args_lst->content, '*'))
					return (ft_exp_err(op_token->word->str, d->progname));
				fd = open(args_lst->content, O_RDONLY);
				ft_lstclear_gc(&args_lst, ft_free);
			}
			if (fd < 0)
				return (ft_open_err(op_token->word->str, d->progname));
			if (op_token->type == op_heredoc)
				fd = ft_open_heredoc(op_token->word->str, d);
		}
		nodes = nodes->next;
	}
	return (fd);
}

int	ft_parse_fdout(t_list *nodes, t_shell_data *d)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;
	t_list			*args_lst;
	int				fd;

	(void)d;
	fd = STDOUT_FILENO;
	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
				break ;
			if (op_token->type == op_out_redirect_trunc)
			{
				if (fd != STDOUT_FILENO)
					close(fd);
				args_lst = ft_parse_cmd_args(op_token->word, d);
				if (ft_str_hasspace(args_lst->content))
					return (ft_exp_err(op_token->word->str, d->progname));
				fd = open(args_lst->content, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
				ft_lstclear_gc(&args_lst, ft_free);
			}
			if (op_token->type == op_out_redirect_append)
			{
				if (fd != STDOUT_FILENO)
					close(fd);
				fd = open(op_token->word->str, O_WRONLY | O_CREAT | O_APPEND,
						0644);
			}
			if (fd < 0)
				return (ft_open_err(op_token->word->str, d->progname));
		}
		nodes = nodes->next;
	}
	return (fd);
}
