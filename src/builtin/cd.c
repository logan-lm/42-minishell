/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:56:23 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 17:55:52 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "minishell.h"

static int	puterr(t_cd_errmode err, char *path, char *progname)
{
	char	*err_str;

	if (err == no_arg)
		return (EXIT_FAILURE);
	if (err == no_home)
		return (ft_print_error("cd: HOME not set", progname));
	if (err == no_access)
	{
		err_str = ft_strjoin_gc_id("cd: ", path, malloc_id_exec);
		ft_print_perror(err_str, progname);
		ft_free(err_str);
		return (EXIT_FAILURE);
	}
	return (1);
}

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

static void	set_pwd(t_shell_data *data, char *new_pwd)
{
	if (chdir(new_pwd) == -1)
		ft_print_perror("", data->progname);
	ft_dictadd(&data->envp, "OLDPWD", ft_getenv(data->envp, "PWD"));
	ft_dictadd(&data->envp, "PWD", new_pwd);
}

static void	ft_close_fd(int fdin, int fdout)
{
	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
}

int	ft_cd(char **args, t_shell_data *data, int fdin, int fdout)
{
	char	*home;
	char	*path;

	ft_close_fd(fdin, fdout);
	args++;
	if (!args)
		return (puterr(no_arg, NULL, data->progname));
	if (!args[0] || (!*args[0] && !*(args + 1)))
	{
		home = ft_dictmap(data->envp, "HOME");
		if (!home)
			return (puterr(no_home, NULL, data->progname));
		set_pwd(data, home);
		return (EXIT_SUCCESS);
	}
	if (*(args + 1))
		return (ft_print_error("cd: too many arguments", data->progname));
	path = ft_parse_path(args[0], data->envp);
	if (!path)
		ft_exit(EXIT_FAILURE);
	if (!access(path, R_OK) && ft_isdir(path))
		set_pwd(data, path);
	else
		return (puterr(no_access, path, data->progname));
	return (EXIT_SUCCESS);
}
