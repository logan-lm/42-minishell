/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:17:19 by pberne            #+#    #+#             */
/*   Updated: 2026/01/13 20:42:45 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

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
/// if there is no
void	ft_add_or_split_cmpd(t_string_compound_lst **cmpd_lst,
		t_list **lst_start, t_list **new_node)
{
	t_string_compound_lst	*current;
	t_string_compound_lst	*temp;
	int						next_space;

	current = *cmpd_lst;
	next_space = ft_get_next_space_index(current->str);
	// no space, we add everything, no need to create new node
	if (next_space < 0 || !current->is_naked)
	{
		temp = current;
		*cmpd_lst = current->next;
		if (current->str[0])
			ft_lst_compound_addback(*new_node, current);
		return ;
	}
	/// contains space further, we split, add the compound to node, push the
	/// finished node and create a new node for the next argument
	else if (next_space > 0)
	{
		temp = ft_copy_str_cmpd_flags(current);
		temp->next = NULL;
		temp->str = ft_substr_gc_id(current->str, 0, next_space,
				malloc_id_exec);
		if (temp->str)
			ft_lst_compound_addback(*new_node, temp);
		ft_lstadd_back(lst_start, *new_node);
		*new_node = ft_lstnew_gc_id(NULL, malloc_id_exec);
		current->str += next_space;
		return ;
	}
	// isspace we skip
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
	t_string_compound_lst	*iterator;
	t_list					*new_node;

	iterator = cmpd_lst;
	new_node = ft_lstnew_gc_id(NULL, malloc_id_exec);
	if (ft_is_cmpd_always_empty(cmpd_lst))
	{
		new_node->content = ft_get_string_token_node("", 0, word_true,
				(t_v2i){0, 0});
		((t_string_compound_lst *)new_node->content)->is_expanded = ft_is_always_expanded(cmpd_lst);
		ft_lstadd_back(lst_start, new_node);
		return ;
	}
	while (cmpd_lst)
		ft_add_or_split_cmpd(&cmpd_lst, lst_start, &new_node);
	if (new_node->content)
		ft_lstadd_back(lst_start, new_node);
}

int	ft_has_naked_star(t_string_compound_lst *cmpd)
{
	while (cmpd)
	{
		if (cmpd->is_naked)
		{
			if (ft_strchr(cmpd->str, '*'))
				return (1);
		}
		cmpd = cmpd->next;
	}
	return (0);
}

void	ft_process_wildcards(t_list **wildcarded_list,
		t_list *post_split_cmpt_list)
{
	t_list	*new_node;

	while (post_split_cmpt_list)
	{
		new_node = NULL;
		if (ft_has_naked_star(post_split_cmpt_list->content))
		{
			new_node = ft_expand_wildcard(post_split_cmpt_list->content);
			if (new_node)
				ft_lstadd_back(wildcarded_list, new_node);
			else
			{
				new_node = ft_lstnew_gc_id(ft_str_compound_to_str(post_split_cmpt_list->content),
						malloc_id_exec);
				ft_lstadd_back(wildcarded_list, new_node);
			}
			post_split_cmpt_list = post_split_cmpt_list->next;
		}
		else
		{
			new_node = ft_lstnew_gc_id(ft_str_compound_to_str(post_split_cmpt_list->content),
					malloc_id_exec);
			ft_lstadd_back(wildcarded_list, new_node);
			post_split_cmpt_list = post_split_cmpt_list->next;
		}
	}
}

t_list	*ft_parse_cmd_args(t_string_compound_lst *lst, t_shell_data *d)
{
	t_string_compound_lst	*iterator;
	t_list					*post_split_cmpt_list;
	t_list					*wildcarded_list;

	post_split_cmpt_list = NULL;
	wildcarded_list = NULL;
	iterator = lst;
	// EXPANSION
	while (iterator)
	{
		ft_expand_tilde(iterator, ft_getvar(d->vars, d->envp, d->argv, "HOME"));
		iterator = iterator->next;
	}
	iterator = lst;
	while (iterator)
	{
		ft_expand_compound(iterator, d);
		iterator = iterator->next;
	}
	// SPLIT
	ft_split_compound_list(&post_split_cmpt_list, lst);
	// CLEAN
	ft_clean_cmpd_list(&post_split_cmpt_list);
	// WILDCARDS
	ft_process_wildcards(&wildcarded_list, post_split_cmpt_list);
	return (wildcarded_list);
}
