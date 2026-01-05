/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:55:10 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 10:17:29 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmerge(t_list *dest, t_list *src)
{
	while (src)
	{
		ft_lstadd_back(&dest, ft_lstnew_gc(src->content));
		src = src->next;
	}
	return (dest);
}
