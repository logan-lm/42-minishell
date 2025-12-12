/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 20:01:39 by pberne            #+#    #+#             */
/*   Updated: 2025/12/02 20:04:47 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_clampi(int nb, int min, int max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}

long	ft_clampl(long nb, long min, long max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}

float	ft_clampf(float nb, float min, float max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}

double	ft_clampd(double nb, double min, double max)
{
	if (nb < min)
		return (min);
	if (nb > max)
		return (max);
	return (nb);
}
