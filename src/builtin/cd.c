/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:56:23 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 12:55:06 by pberne           ###   ########.fr       */
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

static void	set_pwd(t_shell_data *data, char *new_pwd)
{
	if (chdir(new_pwd) == -1)
		ft_print_perror(new_pwd, data->progname);
	new_pwd = getcwd(NULL, 0);
	ft_dictadd(&data->envp, "OLDPWD", ft_getenv_gc_id(data->envp, "PWD",
			malloc_id_exec));
	ft_dictadd(&data->envp, "PWD", new_pwd);
	free(new_pwd);
}

static int	ft_check_args(char **args, t_shell_data *data)
{
	char	*home;

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
	return (2);
}

int	ft_cd(char **args, t_shell_data *data, int fdin, int fdout)
{
	int		ret;
	char	*path;

	if (fdin != STDIN_FILENO)
		close(fdin);
	args++;
	ret = ft_check_args(args, data);
	if (ret != 2)
		return (ret);
	path = ft_parse_path(args[0], data->envp);
	if (!path)
		ft_exit(EXIT_FAILURE);
	if (!access(path, R_OK) && ft_isdir(path))
		set_pwd(data, path);
	else
		return (puterr(no_access, path, data->progname));
	if (!ft_strncmp(args[0], "-", 2))
		ft_putstr_fd(ft_strjoin_gc_id(path, "\n", malloc_id_exec), fdout);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	return (EXIT_SUCCESS);
}
