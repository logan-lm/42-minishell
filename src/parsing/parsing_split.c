/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:17:19 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 07:41:18 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

/// @brief assigns teh compound to the content of lst of it is null or
/// traverse it and adds it to the back of the list if a compound is already
/// present
void	ft_lst_compound_addback(t_list *node, t_string_compound_lst *cmpd)
{
	t_string_compound_lst	*node_cmpd;

	if (!node->content)
		node->content = cmpd;
	else
	{
		node_cmpd = node->content;
		while (node_cmpd->next)
			node_cmpd = node_cmpd->next;
		node_cmpd->next = cmpd;
	}
	cmpd->next = 0;
}

void	ft_advance_to_next_space(t_list **lst_start, t_list **new_node,
		t_string_compound_lst *current, int next_space)
{
	t_string_compound_lst	*temp;

	temp = ft_copy_str_cmpd_flags(current);
	temp->next = NULL;
	temp->str = ft_substr_gc_id(current->str, 0, next_space, malloc_id_exec);
	if (temp->str)
		ft_lst_compound_addback(*new_node, temp);
	ft_lstadd_back(lst_start, *new_node);
	*new_node = ft_lstnew_gc_id(NULL, malloc_id_exec);
	current->str += next_space;
}

/// @brief checks if the current cmpd is a candidate for splitting
///
/// If it is: move to the next space, if there is characters before the space,
/// create a new token with the same flags and assign the remainder to its str
///
/// then: consume the string up to the next non-space character on the right
/// part, if we are not at the end of the string, reassign str to the new
/// valid position. If we reached the end of the compound, advance to the next
/// compound
///
/// if there is spaces, we add the node to the list if it contains something,
/// then create a new node and skip the spaces
void	ft_add_or_split_cmpd(t_string_compound_lst **cmpd_lst,
		t_list **lst_start, t_list **new_node)
{
	t_string_compound_lst	*current;
	int						next_space;

	current = *cmpd_lst;
	next_space = ft_get_next_space_index(current->str);
	if (next_space < 0 || !current->is_naked)
	{
		*cmpd_lst = current->next;
		if (current->str[0])
			ft_lst_compound_addback(*new_node, current);
		return ;
	}
	else if (next_space > 0)
	{
		ft_advance_to_next_space(lst_start, new_node, current, next_space);
		return ;
	}
	else if (next_space == 0)
	{
		if ((*new_node)->content)
			ft_lstadd_back(lst_start, *new_node);
		*new_node = ft_lstnew_gc_id(NULL, malloc_id_exec);
		ft_str_consume_spaces(current);
	}
}

/// @brief Split the compound list if there are unquoted spaces.
/// each node of the created list will be an argument
/// the new compound lists inherits the flags from theirn parent
/// if a split occurs
void	ft_split_compound_list(t_list **lst_start,
		t_string_compound_lst *cmpd_lst)
{
	t_list	*new_node;

	new_node = ft_lstnew_gc_id(NULL, malloc_id_exec);
	if (ft_is_cmpd_always_empty(cmpd_lst))
	{
		new_node->content = ft_get_string_token_node("", 0, word_true,
				(t_v2i){0, 0});
		((t_string_compound_lst *)new_node->content)->is_expanded
			= ft_is_cmpd_always_expanded(cmpd_lst);
		ft_lstadd_back(lst_start, new_node);
		return ;
	}
	while (cmpd_lst)
		ft_add_or_split_cmpd(&cmpd_lst, lst_start, &new_node);
	if (new_node->content)
		ft_lstadd_back(lst_start, new_node);
}
