/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc_formatter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:20:21 by pberne            #+#    #+#             */
/*   Updated: 2026/01/07 11:20:21 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_format_hdoc_cmpd(t_string_compound_lst *lst)
{
	t_string_compound_lst	*start;
	int						not_naked_count;

	not_naked_count = 0;
	start = lst;
	not_naked_count -= lst->is_naked - 1;
	lst = lst->next;
	while (lst)
	{
		start->str = ft_strjoin_gc_id(start->str, lst->str, malloc_id_token);
		not_naked_count += lst->is_naked - 1;
		lst = lst->next;
	}
	start->is_naked = (not_naked_count == 0);
	start->next = 0;
}
