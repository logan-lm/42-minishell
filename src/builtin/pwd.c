/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:39:25 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/28 11:06:41 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_shell_data *data, int fdout)
{
	char	*pwd;

	(void)args;
	(void)data;
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fdout);
	free(pwd);
	ft_putchar_fd('\n', fdout);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	return (0);
}
