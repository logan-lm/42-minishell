/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v3f_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:41:14 by pberne            #+#    #+#             */
/*   Updated: 2025/12/03 12:04:11 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_structs.h"

t_v3f	ft_v3f_add(t_v3f v1, t_v3f v2)
{
	return ((t_v3f){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_v3f	ft_v3f_sub(t_v3f v1, t_v3f v2)
{
	return ((t_v3f){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_v3f	ft_v3f_mult(t_v3f v1, t_v3f v2)
{
	return ((t_v3f){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

t_v3f	ft_v3f_scale(t_v3f v1, float f)
{
	return ((t_v3f){v1.x * f, v1.y * f, v1.z * f});
}
