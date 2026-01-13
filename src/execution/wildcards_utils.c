/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:17:22 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/13 16:11:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

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

t_list	*ft_expand_wildcard(t_string_compound_lst *cmpd)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*filenames;

	lst = NULL;
	filenames = ft_get_sorted_dircontent("", 0);
	if (!filenames)
		return (NULL);
	while (filenames)
	{
		if (ft_is_pattern_matching_cmpd(filenames->content, cmpd))
		{
			tmp = filenames;
			filenames = filenames->next;
			ft_lstadd_back(&lst, tmp);
			tmp->next = 0;
		}
		else
			filenames = filenames->next;
	}
	return (lst);
}
