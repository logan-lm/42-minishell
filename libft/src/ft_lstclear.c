/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:26:32 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 17:37:54 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_r(t_list *lst, void (*del)(void *))
{
	if (lst->next)
		ft_lstclear_r(lst->next, del);
	if (del)
		del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!*lst)
		return ;
	ft_lstclear_r(*lst, del);
	*lst = 0;
}

void	ft_lstclear_gc_r(t_list *lst, void (*del)(void *))
{
	if (lst->next)
		ft_lstclear_r(lst->next, del);
	if (del)
		del(lst->content);
	ft_free(lst);
}

void	ft_lstclear_gc(t_list **lst, void (*del)(void *))
{
	if (!*lst)
		return ;
	ft_lstclear_gc_r(*lst, del);
	*lst = 0;
}
