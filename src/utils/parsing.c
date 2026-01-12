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
