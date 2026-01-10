/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:45:19 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 14:26:30 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// @brief Takes strings as a pointer on strings and writes on STDOUT
// @param args pointers on strings as echo command arguments (-n in first arg)
// @return void
//
void	ft_consume_stdin(int fdin)
{
	char buffer[4096];
	ssize_t bytes_read;

	if (fdin == STDIN_FILENO)
		return ;
	while ((bytes_read = read(fdin, buffer, sizeof(buffer))) > 0)
			;
	close(fdin);
}