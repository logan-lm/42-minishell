/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:39:25 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 11:22:07 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_shell_data *data, int fdin, int fdout)
{
	char	*pwd;

	if (fdin != STDIN_FILENO)
		close(fdin);
	(void)args;
	(void)data;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_add_exit(pwd, free);
	ft_putstr_fd(pwd, fdout);
	free(pwd);
	ft_putchar_fd('\n', fdout);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	return (0);
}
