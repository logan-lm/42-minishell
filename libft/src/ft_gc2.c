/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:05:13 by pberne            #+#    #+#             */
/*   Updated: 2025/11/24 16:58:02 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"

void	*ft_malloc(unsigned long size)
{
	return (ft_gc(GC_ALLOC, size));
}

void	ft_free(void *ptr)
{
	ft_gc(GC_FREE, (uintptr_t) ptr);
}

void	ft_clear_gc(void)
{
	ft_gc(GC_CLEARALL, 0);
}
