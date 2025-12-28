/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:43:45 by pberne            #+#    #+#             */
/*   Updated: 2025/12/28 21:18:59 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fdl(long n, int fd)
{
	char	c;
	int		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i += write(fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fdl(n / 10, fd);
	c = '0' + n % 10;
	i += write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr_fdl(n, fd);
}
