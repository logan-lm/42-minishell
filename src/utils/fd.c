/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:45:19 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/06 11:46:15 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_fd(int flag, int fd)
{
	static int	s_fd = 0;

	if (flag == 0)
		return (s_fd);
	if (flag == 1)
		s_fd = fd;
	return (0);
}

int	ft_getfd(void)
{
	return (ft_fd(0, 0));
}

void	ft_setfd(int fd)
{
	ft_fd(1, fd);
}
