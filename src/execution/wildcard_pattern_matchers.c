/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_pattern_matchers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:55:37 by pberne            #+#    #+#             */
/*   Updated: 2026/01/12 22:24:05 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_match_here(char *src, t_string_compound_lst *node, int i)
{
	if (node->str[i] == '\0')
		return (ft_is_pattern_matching_cmpd(src, node->next));
	if (node->is_naked && node->str[i] == '*')
	{
		if (ft_match_here(src, node, i + 1))
			return (1);
		if (*src != '\0' && ft_match_here(src + 1, node, i))
			return (1);
		return (0);
	}
	if (*src != '\0' && *src == node->str[i])
		return (ft_match_here(src + 1, node, i + 1));
	return (0);
}

int	ft_is_pattern_matching_cmpd(char *src, t_string_compound_lst *pattern_lst)
{
	if (!pattern_lst)
		return (*src == '\0');
	if (!pattern_lst->str || !pattern_lst->str[0])
		return (ft_is_pattern_matching_cmpd(src, pattern_lst->next));
	return (ft_match_here(src, pattern_lst, 0));
}

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
