/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:36:46 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/28 21:55:59 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strhasequal(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '=')
			return (i);
	return (0);
}

int	ft_export(char **args, t_shell_data *data, int fdout)
{
	int		i;
	int		set_mode;
	t_dict	var_entry;

	if (fdout != STDOUT_FILENO)
		close(fdout);
	i = -1;
	args++;
	while (args[++i])
	{
		set_mode = ft_strhasequal(args[i]);
		var_entry.key = ft_malloc((set_mode + 2) * sizeof(char));
		ft_strlcpy(var_entry.key, args[i], set_mode + 2);
		if (set_mode)
		{
			var_entry.value = ft_strdup_gc(args[i] + set_mode + 1);
			ft_dictadd(&data->vars, var_entry.key, var_entry.value);
		}
		else
			var_entry.value = ft_dictmap(data->vars, args[i]);
		ft_dictadd(&data->envp, var_entry.key, var_entry.value);
	}
	return (EXIT_SUCCESS);
}
