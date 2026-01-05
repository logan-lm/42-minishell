/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:44:14 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 17:13:56 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_pid(int flag, int pid)
{
	static int	s_pid = 0;

	if (flag == 0)
		return (s_pid);
	if (flag == 1)
		s_pid = pid;
	return (0);
}

int	ft_getpid(void)
{
	return (ft_pid(0, 0));
}

void	ft_setpid(int pid)
{
	ft_pid(1, pid);
}
