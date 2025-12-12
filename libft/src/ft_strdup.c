/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:01:40 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 19:02:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*s;
	size_t	size;
	size_t	i;

	i = 0;
	s = (char *)s1;
	size = ft_strlen(s);
	str = malloc(size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

char	*ft_strdup_gc(const char *s1)
{
	char	*str;
	char	*s;
	size_t	size;
	size_t	i;

	i = 0;
	s = (char *)s1;
	size = ft_strlen(s);
	str = ft_malloc(size + 1);
	str[size] = '\0';
	while (i < size)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
