/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:56:23 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/18 15:18:11 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	ft_isdir(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (!S_ISDIR(path_stat.st_mode))
	{
		errno = 20;
		return (0);
	}
	return (1);
}

void	cd(char **args, t_list *envp)
{
	if (!args)
		return (1);
	if (*(args + 1))
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (!*args)
		ft_dictadd(&envp, "PWD", ft_dictmap(envp, "HOME"));
	else if (!access(*args, R_OK) && ft_isdir(*args))
		ft_dictadd(&envp, "PWD", *args);
	else
		perror("minishell ");
}
