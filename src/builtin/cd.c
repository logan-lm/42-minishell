/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:56:23 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/18 14:04:01 by lomartin         ###   ########.fr       */
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

void	cd(char *path, t_shell_data *s_data)
{
	if (!path)
		ft_dictadd(&s_data->envp, "PWD", ft_dictmap(s_data->envp, "HOME"));
	else if (!access(path, R_OK) && ft_isdir(path))
		ft_dictadd(&s_data->envp, "PWD", path);
	else
		perror("minishell ");
}
