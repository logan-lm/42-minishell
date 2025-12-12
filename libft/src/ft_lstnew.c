/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:48:55 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 17:36:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->next = 0;
	new->content = content;
	return (new);
}

t_list	*ft_lstnew_gc(void *content)
{
	t_list	*new;

	new = ft_malloc(sizeof(t_list));
	new->next = 0;
	new->content = content;
	return (new);
}
