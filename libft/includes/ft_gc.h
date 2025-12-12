/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:13:08 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 17:08:18 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GC_H
# define FT_GC_H

# include <stdint.h>
# include <stdlib.h>

# define GC_ALLOC 0
# define GC_FREE 1
# define GC_CLEARALL 2
# define GC_HASHTABLE_SIZE 16411

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

void					*ft_gc(int flag, uintptr_t size);
void					*ft_malloc(unsigned long size);
void					ft_free(void *ptr);
void					ft_clear_gc(void);

#endif
