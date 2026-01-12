/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:45:19 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/12 14:29:21 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*ft_progname(int flag, char *progname)
{
	static char	*s_progname = 0;

	if (flag == 0)
		return (s_progname);
	if (flag == 1)
		s_progname = progname;
	return (0);
}

char	*ft_get_progname(void)
{
	return (ft_progname(0, 0));
}

void	ft_set_progname(char *progname)
{
	ft_progname(1, progname);
}
