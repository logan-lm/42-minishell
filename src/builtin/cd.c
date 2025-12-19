/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:56:23 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/19 19:09:53 by lomartin         ###   ########.fr       */
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

int	ft_cd(char **args, t_list *envp)
{
	char	*home;
	char	*path;
	char	*err_str;

	if (!args)
		return (EXIT_FAILURE);
	if (*(args + 1))
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (!args[0] || !*args[0])
	{
		home = ft_dictmap(envp, "HOME");
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		ft_dictadd(&envp, "PWD", home);
	}
	path = ft_parse_path(args[0], envp);
	if (!access(path, R_OK) && ft_isdir(path))
		ft_dictadd(&envp, "PWD", path);
	else
	{
		err_str = ft_strjoin("minishell: cd: ", path);
		perror(err_str);
		ft_free(err_str);
		return (EXIT_FAILURE);
	}
	free(path);
	return (EXIT_SUCCESS);
}
