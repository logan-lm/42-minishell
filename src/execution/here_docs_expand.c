/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:14:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 16:41:16 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

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
