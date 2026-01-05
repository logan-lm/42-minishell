/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:04:24 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 18:00:41 by lomartin         ###   ########.fr       */
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

/// n_l : namelen, a_m : append_mode
int	ft_set_var(char **args, t_shell_data *data, int fdin, int fdout)
{
	t_dict	*var;
	int		n_l;
	int		a_m;
	char	*temp;

	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	var = ft_calloc_gc_id(1, sizeof(t_dict), malloc_id_exec);
	a_m = ft_set_append_mode(*args);
	n_l = ft_strclen(*args, '=');
	var->key = ft_calloc_gc_id(n_l + 1 - a_m, sizeof(char), malloc_id_exec);
	ft_strlcpy(var->key, *args, n_l + 1 - a_m);
	if (a_m)
		var->value = ft_getvar(data->vars, data->envp, var->key);
	temp = var->value;
	var->value = ft_strjoin_gc_id(var->value, *args + n_l + 1, malloc_id_exec);
	ft_free(temp);
	if (ft_dictmap(data->envp, var->key))
		ft_dictadd(&data->envp, var->key, var->value);
	ft_dictadd(&data->vars, var->key, var->value);
	ft_free(var);
	return (0);
}
