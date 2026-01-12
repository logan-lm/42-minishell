/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:26:19 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/12 13:39:00 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save_src(t_list **src)
{
	if (!*src)
		ft_lstadd_back(src, ft_lstnew_gc_id(ft_strdup_gc_id("", malloc_id_exec),
				malloc_id_exec));
}

char	**ft_join_strs(char *str, char **strs, char *var)
{
	size_t	strs_len;
	size_t	i;
	size_t	j;
	char	**dest;

	strs_len = -1;
	while (strs[++strs_len])
		;
	if (str && *str && ((var && ft_isspace(*var)) || !var))
		++strs_len;
	dest = ft_malloc_id((strs_len + 2) * sizeof(char *), malloc_id_exec);
	dest[strs_len] = NULL;
	i = -1;
	if (str && *str && ((var && ft_isspace(*var)) || !var))
		dest[++i] = str;
	else
		strs[0] = ft_strjoin_gc_id(str, strs[0], malloc_id_exec);
	j = -1;
	while (strs[++j])
		dest[++i] = strs[j];
	if (var && ft_isspace(var[ft_strlen(var) - 1]))
		dest[++i] = "";
	else
		dest[++i] = NULL;
	return (dest);
}
