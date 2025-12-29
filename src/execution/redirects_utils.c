/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:16:04 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/29 10:31:10 by lomartin         ###   ########.fr       */
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

int	ft_exp_err(int fd, char *filename)
{
	char *err;

	err = ft_strjoin_mult_gc(3, "minishell: ", filename, ": ambiguous redirect\n");
	ft_putstr_fd(err, 2);
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
