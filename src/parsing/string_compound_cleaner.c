/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_compound_cleaner.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:00:44 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 11:25:07 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_scrap_empty_cmpd_nodes(t_string_compound_lst **cmpd)
{
	t_string_compound_lst	*current;
	t_string_compound_lst	*prev;

	current = *cmpd;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->str, "") == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*cmpd = current->next;
		}
		else
			prev = current;
		current = current->next;
	}
}

/// @brief checks if a compound is removeable and clean the data
///
/// if not removeable we do the following
///
/// if the content is always empty and at least one node is quoted
/// we replace the cmprd with a single empty node
///
/// if there is some content, we remove every empty nodes from the
/// compound list
int	ft_is_cmpd_removeable(t_string_compound_lst **cmpd)
{
	t_string_compound_lst	*temp;

	if (ft_is_cmpd_always_naked(*cmpd) && ft_is_cmpd_always_empty(*cmpd))
		return (1);
	else
	{
		if (ft_is_cmpd_always_empty(*cmpd))
		{
			temp = ft_get_string_token_node("", 0, word_true, (t_v2i){0, 0});
			temp->is_expanded = ft_is_cmpd_always_expanded(*cmpd);
			*cmpd = temp;
		}
		else
			ft_scrap_empty_cmpd_nodes(cmpd);
		return (0);
	}
}

void	ft_clean_cmpd_list(t_list **lst)
{
	t_list	*prev;
	t_list	*current;

	current = *lst;
	prev = NULL;
	while (current)
	{
		if (ft_is_cmpd_removeable((t_string_compound_lst **)&current->content))
		{
			if (prev)
				prev->next = current->next;
			else
				*lst = current->next;
		}
		else
			prev = current;
		current = current->next;
	}
}
