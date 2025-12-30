/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:36:46 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/30 16:03:13 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_set_append_mode(char *varname)
{
	size_t	varname_len;

	varname_len = ft_strclen(varname, '=');
	if (varname_len > 0 && varname[varname_len - 1] == '+')
		return (1);
	return (0);
}

static int	ft_strhasequal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (i);
	return (0);
}

int	ft_export(char **args, t_shell_data *data, int fdin, int fdout)
{
	int		i;
	int		set_mode;
	int		append_mode;
	t_dict	var_entry;

	if(fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	i = -1;
	args++;
	while (args[++i])
	{
		set_mode = ft_strhasequal(args[i]);
		append_mode = ft_set_append_mode(args[i]);
		var_entry.key = ft_malloc((ft_strclen(args[i], '=') + 2 - set_mode
					- append_mode) * sizeof(char));
		ft_strlcpy(var_entry.key, args[i], (ft_strclen(args[i], '=') + 2
				- set_mode - append_mode));
		if (set_mode)
			ft_set_var((char *[2]){args[i], NULL}, data, fdin, fdout);
		var_entry.value = ft_dictmap(data->vars, var_entry.key);
		ft_dictadd(&data->envp, var_entry.key, var_entry.value);
	}
	return (EXIT_SUCCESS);
}
