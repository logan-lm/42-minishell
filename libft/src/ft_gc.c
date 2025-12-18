/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:59:30 by pberne            #+#    #+#             */
/*   Updated: 2025/12/18 14:09:25 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_gc_do_print_count(t_gc_node **hash_table);

void	ft_free_node_list(t_gc_node *node)
{
	if (node)
	{
		ft_free_node_list(node->next);
		free(node->ptr);
		free(node);
	}
}

void	ft_free_ptr(t_gc_node **hashtable, void *ptr)
{
	long		index;
	t_gc_node	*node;
	t_gc_node	*prev;

	index = ((uintptr_t)ptr) % GC_HASHTABLE_SIZE;
	node = hashtable[index];
	prev = 0;
	while (node)
	{
		if (node->ptr == ptr)
		{
			if (prev)
				prev->next = node->next;
			else
				hashtable[index] = node->next;
			free(node->ptr);
			free(node);
			return ;
		}
		else
		{
			prev = node;
			node = node->next;
		}
	}
}

void	ft_gc_free_all(t_gc_node **hashtable)
{
	unsigned long	i;

	i = 0;
	while (i < GC_HASHTABLE_SIZE)
	{
		ft_free_node_list(hashtable[i]);
		hashtable[i] = 0;
		i++;
	}
}

void	*ft_gc_alloc(t_gc_node **hashtable, uintptr_t size)
{
	unsigned long	index;
	void			*ptr;
	t_gc_node		*node;

	ptr = malloc((size_t)size);
	if (!ptr)
		ft_exit(MALLOC_FAILED);
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		ft_exit(MALLOC_FAILED);
	}
	node->ptr = ptr;
	index = ((uintptr_t)ptr) % GC_HASHTABLE_SIZE;
	if (hashtable[index])
		node->next = hashtable[index];
	else
		node->next = 0;
	hashtable[index] = node;
	return (ptr);
}

/// @brief Keeps track of allocated memory
/// @param flag GC_ALLOC, GC_FREE, GC_CLEARALL
/// @param size represents either a size_t or pointer address
void	*ft_gc(int flag, uintptr_t var)
{
	static t_gc_node	*hash_table[GC_HASHTABLE_SIZE];
	static int			zeroed = 0;

	if (!zeroed)
	{
		zeroed = 1;
		ft_bzero(hash_table, GC_HASHTABLE_SIZE * sizeof(t_gc_node *));
	}
	if (flag == GC_ALLOC)
		return (ft_gc_alloc(hash_table, var));
	else if (flag == GC_FREE)
		ft_free_ptr(hash_table, (void *)var);
	else if (flag == GC_CLEARALL)
		ft_gc_free_all(hash_table);
	else if (flag == GC_PRINT_COUNT)
		ft_gc_do_print_count(hash_table);
	return (0);
}
