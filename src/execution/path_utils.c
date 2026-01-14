/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:04:22 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 08:57:53 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

char	*ft_check_paths(char *cmdname, t_list *envp)
{
	char	*temp;
	char	**paths;
	int		i;

	temp = ft_dictmap_gc_id(envp, "PATH", malloc_id_exec);
	if (!temp)
		return (NULL);
	paths = ft_split_gc_id(temp, ':', malloc_id_exec);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_mult_gc_id(malloc_id_exec, 3, paths[i], "/", cmdname);
		if (!ft_isdir(temp) && !access(temp, F_OK))
		{
			ft_free_strs(paths);
			return (temp);
		}
		ft_free(temp);
		i++;
	}
	ft_free_strs(paths);
	return (NULL);
}

int	ft_check_cmdaccess(char *path, char *progname, int *ret)
{
	char	*err;

	if (ft_isdir(path))
	{
		err = ft_strjoin_gc_id(path, ": Is a directory", malloc_id_exec);
		*ret = 126;
		ft_print_error(err, progname);
		ft_free(err);
		return (0);
	}
	if (access(path, F_OK))
	{
		*ret = 127;
		ft_print_perror(path, progname);
		return (0);
	}
	if (access(path, R_OK | X_OK))
	{
		*ret = 126;
		ft_print_perror(path, progname);
		return (0);
	}
	return (1);
}

char	*ft_get_cmdpath(char *cmd, t_list *envp, int *ret, char *progname)
{
	char	*path;

	if (ft_ispath(cmd) || !*ft_getenv_gc_id(envp, "PATH", malloc_id_exec))
	{
		if (ft_check_cmdaccess(cmd, progname, ret))
			return (ft_parse_path(cmd, envp));
		else
			return (NULL);
	}
	path = ft_check_paths(cmd, envp);
	if (path)
		return (path);
	ft_free(path);
	if (errno == 13)
	{
		ft_print_perror(cmd, progname);
		*ret = 126;
	}
	else
	{
		ft_print_error(ft_strjoin_gc_id(cmd, ": command not found",
				malloc_id_exec), progname);
		*ret = 127;
	}
	return (NULL);
}
