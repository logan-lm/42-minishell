/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 09:01:37 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/28 19:22:32 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_err(int fd, char *filename)
{
	char *err;

	err = ft_strjoin_mult_gc(3, "minishell: ", filename, ": ");
	perror(err);
	ft_free(err);
	return (fd);
}

int	is_limiter(char *str, char *limiter)
{
	size_t	len;
	size_t	llen;

	if (!str)
		return (0);
	len = ft_strlen(str);
	llen = ft_strlen(limiter);
	if (str[len - 1] != '\n')
		return (0);
	len--;
	while (len > 0 && llen > 0 && str[len - 1] != '\n')
	{
		if (str[len-- - 1] != limiter[llen-- - 1])
			return (0);
	}
	if (!llen && (!len || str[len - 1] == '\n'))
		return (1);
	return (0);
}

int	ft_open_heredoc(char *limiter)
{
	char	*filename;
	int		temp_w;
	int		temp_r;
	char	*buffer;
	char	*line;
	char	*err;

	filename = ft_itoa_gc((long)limiter);
	temp_w = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	temp_r = open(filename, O_RDONLY);
	unlink(filename);
	buffer = NULL;
	if (temp_r == -1 || temp_w == -1)
		return (1);
	while (!is_limiter(line, limiter))
	{
		ft_free(line);
		buffer = readline("> ");
		line = ft_strjoin_gc(buffer, "\n");
		free(buffer);
		if (!buffer)
		{
			err = ft_strjoin_mult_gc(3, "minishell: warning: here-document at line ?? delimited by end-of-file (wanted `", limiter, "')\n");
			ft_putstr_fd(err, 2);
			ft_free(err);
			return (-1);
		}
		if (is_limiter(line, limiter))
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
	//t_list			*args_lst;
	int				fd;

	(void)d;
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
				fd = open(op_token->word->str, O_RDONLY);
			if (fd < 0)
				return (ft_open_err(fd, op_token->word->str));
			if (op_token->type == op_heredoc)
				fd = ft_open_heredoc(op_token->word->str);
		}
		nodes = nodes->next;
	}
	return (fd);
}

int	ft_parse_fdout(t_list *nodes, t_shell_data *d)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;
	//t_list			*args_lst;
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
				fd = open(op_token->word->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			if (op_token->type == op_out_redirect_append)
			{
				if (fd != STDOUT_FILENO)
					close(fd);
				fd = open(op_token->word->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			if (fd < 0)
				return (ft_open_err(fd, op_token->word->str));
		}
		nodes = nodes->next;
	}
	return (fd);
}

int	ft_has_pipe(t_list *nodes)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;

	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
				return (1);
		}
		nodes = nodes->next;
	}
	return (0);
}

t_list *ft_next_cmd(t_list *nodes)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;

	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
				return (nodes->next);
		}
		nodes = nodes->next;
	}
	return (NULL);
}
