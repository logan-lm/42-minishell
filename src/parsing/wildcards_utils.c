/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:17:22 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 07:12:37 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

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

t_list	*ft_wc_node(t_list *src, int id)
{
	t_list	*new_node;

	new_node = ft_lstnew_gc_id(ft_str_cmpd_to_str(src->content), id);
	return (new_node);
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
				new_node = ft_wc_node(post_split_cmpt_list, malloc_id_exec);
				ft_lstadd_back(wildcarded_list, new_node);
			}
			post_split_cmpt_list = post_split_cmpt_list->next;
		}
		else
		{
			new_node = ft_wc_node(post_split_cmpt_list, malloc_id_exec);
			ft_lstadd_back(wildcarded_list, new_node);
			post_split_cmpt_list = post_split_cmpt_list->next;
		}
	}
}

void	ft_append_followingpath(t_list *filenames, char *word)
{
	char	*post_wildcard;
	char	*temp;

	post_wildcard = ft_strchr(word, '*') + 1;
	post_wildcard = ft_strchr(post_wildcard, '/');
	while (filenames)
	{
		temp = filenames->content;
		filenames->content = ft_strjoin_gc_id(filenames->content, post_wildcard,
				malloc_id_exec);
		ft_free(temp);
		filenames = filenames->next;
	}
}

size_t	ft_pathsizebeforewildcard(char *word)
{
	size_t	len;
	size_t	i;

	i = -1;
	len = 0;
	while (word[len + ++i])
	{
		if (word[len + i] == '*')
			return (len);
		if (word[len + i] == '/')
		{
			len += i + 1;
			i = -1;
		}
	}
	return (0);
}
