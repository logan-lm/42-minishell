/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:28:42 by pberne            #+#    #+#             */
/*   Updated: 2025/12/17 14:56:23 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	i;
	char	*out;

	str_len = ft_strlen(str);
	if (start >= str_len)
		len = 0;
	else if (start + len > str_len)
		len = str_len - start;
	out = malloc(len + 1);
	if (out == 0)
		return (out);
	i = 0;
	while (i < len)
	{
		out[i] = str[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_substr_gc(const char *str, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	i;
	char	*out;

	str_len = ft_strlen(str);
	if (start >= str_len)
		len = 0;
	else if (start + len > str_len)
		len = str_len - start;
	out = ft_malloc(len + 1);
	i = 0;
	while (i < len)
	{
		out[i] = str[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
