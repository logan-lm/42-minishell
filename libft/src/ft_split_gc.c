/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_gc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:58:29 by pberne            #+#    #+#             */
/*   Updated: 2025/12/12 17:56:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_malloc_split_gc(int depth)
{
	char	**out;

	out = ft_malloc(sizeof(char *) * (depth + 1));
	out[depth] = 0;
	return (out);
}

char	**ft_split_r_gc(char *str, char c, int index, int depth)
{
	char	**out;
	int		start;
	int		end;

	while (str[index] && str[index] == c)
		index++;
	if (!str[index])
		return (ft_malloc_split_gc(depth));
	start = index;
	while (str[index] && str[index] != c)
		index++;
	end = index;
	out = ft_split_r_gc(str, c, index, depth + 1);
	out[depth] = ft_substr_gc(str, start, end - start);
	return (out);
}

char	**ft_split_gc(char const *s, char c)
{
	return (ft_split_r_gc((char *)s, c, 0, 0));
}

void	ft_free_split_gc(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}
