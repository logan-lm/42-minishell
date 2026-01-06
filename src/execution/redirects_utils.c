/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:16:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 23:11:10 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_err(char *filename, char *progname)
{
	char	*err;

	err = ft_strjoin_gc_id(filename, ": ", malloc_id_exec);
	ft_print_perror(err, progname);
	ft_free(err);
	return (-1);
}

int	ft_exp_err(char *filename, char *progname)
{
	char	*err;

	err = ft_strjoin_gc_id(filename, ": ambiguous redirect", malloc_id_exec);
	ft_print_error(err, progname);
	ft_free(err);
	return (-1);
}

char	*ft_heredoc_eof_err(t_shell_data *data, char *limiter, int fd_w,
		char *filename)
{
	char	*err;
	char	*lines;

	close(fd_w);
	lines = ft_itoa_gc_id(data->lines, malloc_id_exec);
	err = ft_strjoin_mult_gc_id(malloc_id_exec, 5,
			"warning: here-document at line ", lines,
			" delimited by end-of-file (wanted `", limiter, "')");
	ft_print_error(err, data->progname);
	return (filename);
}

int	ft_is_limiter(char *str, char *limiter)
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

int	ft_str_hasspace(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			return (1);
		str++;
	}
	return (0);
}
