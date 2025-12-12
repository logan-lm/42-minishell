/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:21:20 by pberne            #+#    #+#             */
/*   Updated: 2025/12/03 09:49:39 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_v2f	ft_v2f(float x, float y)
{
	t_v2f	v2;

	v2.x = x;
	v2.y = y;
	return (v2);
}

t_v2f	*ft_v2fp(float x, float y)
{
	t_v2f	*v2;

	v2 = malloc(sizeof(t_v2f));
	if (!v2)
		return (0);
	v2->x = x;
	v2->y = y;
	return (v2);
}

t_v3f	ft_v3f(float x, float y, float z)
{
	t_v3f	v3;

	v3.x = x;
	v3.y = y;
	v3.z = z;
	return (v3);
}

t_v3f	*ft_v3fp(float x, float y, float z)
{
	t_v3f	*v3;

	v3 = malloc(sizeof(t_v3f));
	if (!v3)
		return (0);
	v3->x = x;
	v3->y = y;
	v3->z = z;
	return (v3);
}
