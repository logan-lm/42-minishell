/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:55:37 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 18:10:01 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_lerpi(int a, int b, float t)
{
	return ((int)((1.0f - t) * (float)a + t * (float)b));
}

int	ft_lerpf(float a, float b, float t)
{
	return ((1.0f - t) * a + t * b);
}

int	ft_lerpd(double a, double b, double t)
{
	return ((1.0 - t) * a + t * b);
}
