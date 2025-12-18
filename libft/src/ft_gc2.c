/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:05:13 by pberne            #+#    #+#             */
/*   Updated: 2025/12/18 10:49:32 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"
#include "libft.h"

void	*ft_malloc(unsigned long size)
{
	return (ft_gc(GC_ALLOC, size));
}

void	ft_free(void *ptr)
{
	ft_gc(GC_FREE, (uintptr_t)ptr);
}

void	ft_clear_gc(void)
{
	ft_gc(GC_CLEARALL, 0);
}

void	ft_gc_print_count(void)
{
	ft_gc(GC_PRINT_COUNT, 0);
}

void	ft_gc_do_print_count(t_gc_node **hash_table)
{
	size_t		i;
	size_t		count;
	t_gc_node	*temp;

	i = 0;
	count = 0;
	while (i < GC_HASHTABLE_SIZE)
	{
		temp = hash_table[i];
		while (temp)
		{
			count++;
			temp = temp->next;
		}
		i++;
	}
	ft_printf("GC count : %l\n", count);
}
