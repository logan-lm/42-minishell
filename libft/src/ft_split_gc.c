/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:58:29 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 18:05:13 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_malloc_split(int depth)
{
	char	**out;

	out = ft_malloc(sizeof(char *) * (depth + 1));
	out[depth] = 0;
	return (out);
}

char	**ft_split_r(char *str, char c, int index, int depth)
{
	char	**out;
	int		start;
	int		end;

	while (str[index] && str[index] == c)
		index++;
	if (!str[index])
		return (ft_malloc_split(depth));
	start = index;
	while (str[index] && str[index] != c)
		index++;
	end = index;
	out = ft_split_r(str, c, index, depth + 1);
	out[depth] = ft_substr_gc(str, start, end - start);
	return (out);
}

char	**ft_split_gc(char const *s, char c)
{
	return (ft_split_r((char *)s, c, 0, 0));
}
