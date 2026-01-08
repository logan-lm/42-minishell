/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:44:14 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/08 16:29:18 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_hd(int flag, int hd)
{
	static int	s_hd = 0;

	if (flag == 0)
		return (s_hd);
	if (flag == 1)
		s_hd = hd;
	return (0);
}

int	ft_gethd(void)
{
	return (ft_hd(0, 0));
}

void	ft_sethd(int hd)
{
	ft_hd(1, hd);
}
