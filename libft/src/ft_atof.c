/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 01:23:17 by pberne            #+#    #+#             */
/*   Updated: 2025/12/06 11:56:00 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_atof_data_init(t_atof_data *d)
{
	d->divider = 10.0;
	d->is_decimal = 0;
	d->nb = 0.0;
	d->i = 0;
	d->sign = 1.0;
}

void	ft_skip_space_sign(t_atof_data *d, char *str)
{
	while (str[d->i] == ' ')
		d->i += 1;
	while (str[d->i] == '-' || str[d->i] == '+')
	{
		if (str[d->i] == '-')
			d->sign *= -1.0f;
		d->i += 1;
	}
}

float	ft_atof(char *str)
{
	t_atof_data	d;

	ft_atof_data_init(&d);
	ft_skip_space_sign(&d, str);
	while (ft_strchr(".0123456789", str[d.i]))
	{
		if (str[d.i] == '.')
			d.is_decimal = 1;
		else if (!d.is_decimal)
		{
			d.nb *= 10.0f;
			d.nb += (double)(str[d.i] - '0');
		}
		else
		{
			d.nb += (double)(str[d.i] - '0') / d.divider;
			d.divider *= 10.0f;
		}
		d.i += 1;
	}
	return ((float)(d.nb * d.sign));
}
