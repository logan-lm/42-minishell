/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_unsigned_long.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:07:13 by pberne            #+#    #+#             */
/*   Updated: 2025/12/03 09:51:03 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_v2ul	ft_v2ul(unsigned long x, unsigned long y)
{
	t_v2ul	v2;

	v2.x = x;
	v2.y = y;
	return (v2);
}

t_v2ul	*ft_v2ulp(unsigned long x, unsigned long y)
{
	t_v2ul	*v2;

	v2 = malloc(sizeof(t_v2ul));
	if (!v2)
		return (0);
	v2->x = x;
	v2->y = y;
	return (v2);
}

t_v3ul	ft_v3ul(unsigned long x, unsigned long y, unsigned long z)
{
	t_v3ul	v3;

	v3.x = x;
	v3.y = y;
	v3.z = z;
	return (v3);
}

t_v3ul	*ft_v3ulp(unsigned long x, unsigned long y, unsigned long z)
{
	t_v3ul	*v3;

	v3 = malloc(sizeof(t_v3ul));
	if (!v3)
		return (0);
	v3->x = x;
	v3->y = y;
	v3->z = z;
	return (v3);
}
