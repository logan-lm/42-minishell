/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:55:37 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 07:52:25 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

t_list	*ft_expand_wildcard(t_string_compound_lst *cmpd)
{
	t_list	*lst;
	t_list	*tmp;
	t_list	*filenames;
	int		include_hidden;

	include_hidden = cmpd->str[0] == '.';
	lst = NULL;
	filenames = ft_get_sorted_dircontent("", 0, include_hidden);
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
