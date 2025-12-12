/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:07:13 by pberne            #+#    #+#             */
/*   Updated: 2025/11/21 18:25:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_v2i	ft_v2i(int x, int y)
{
	t_v2i	v2;

	v2.x = x;
	v2.y = y;
	return (v2);
}

t_v2i	*ft_v2ip(int x, int y)
{
	t_v2i	*v2;

	v2 = malloc(sizeof(t_v2i));
	if (!v2)
		return (0);
	v2->x = x;
	v2->y = y;
	return (v2);
}

t_v3i	ft_v3i(int x, int y, int z)
{
	t_v3i	v3;

	v3.x = x;
	v3.y = y;
	v3.z = z;
	return (v3);
}

t_v3i	*ft_v3ip(int x, int y, int z)
{
	t_v3i	*v3;

	v3 = malloc(sizeof(t_v3i));
	if (!v3)
		return (0);
	v3->x = x;
	v3->y = y;
	v3->z = z;
	return (v3);
}
