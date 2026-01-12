/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:55:37 by pberne            #+#    #+#             */
/*   Updated: 2026/01/12 10:18:57 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_pattern_matching(char *src, char *pattern)
{
	if (!*src)
	{
		if (!*pattern)
			return (1);
		else if (*pattern == '*' && pattern[1] == '\0')
			return (1);
		else
			return (0);
	}
	if (*pattern == '*')
	{
		if (ft_is_pattern_matching(src + 1, pattern))
			return (1);
		if (*src && ft_is_pattern_matching(src, pattern + 1))
			return (1);
		return (0);
	}
	else if (*src && (*src == *pattern))
		return (ft_is_pattern_matching(src + 1, pattern + 1));
	return (0);
}

void	ft_combine_wildcards(char *pattern)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pattern[i])
	{
		pattern[j] = pattern[i];
		if (pattern[i] != '*')
			i++;
		else
		{
			while (pattern[i] == '*')
				i++;
		}
		j++;
	}
	pattern[j] = '\0';
}

/// @brief Returns a list containing the strings from src that matches the
///	pattern
/// @param src null terminated array of strings
/// @param pattern patter is of format "a*b*c", variables have already been
/// interpreted here.
t_list	*ft_get_matching_names(t_list *src, char *pattern)
{
	t_list	*lst;

	lst = 0;
	if (!pattern)
		return (src);
	ft_combine_wildcards(pattern);
	while (src)
	{
		if (ft_is_pattern_matching(src->content, pattern))
			ft_lstadd_back(&lst, ft_lstnew_gc_id(src->content,
					malloc_id_token));
		src = src->next;
	}
	return (lst);
}

t_list	*ft_chech_matchs(t_list *args, t_shell_data *data)
{
	args = ft_get_matching_names(args, data->wc_path);
	if (!args)
		ft_lstadd_front(&args, ft_lstnew_gc_id(data->wc_path, malloc_id_exec));
	return (args);
}
