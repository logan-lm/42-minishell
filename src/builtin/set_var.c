/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:04:24 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/30 15:58:57 by lomartin         ###   ########.fr       */
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

int	ft_set_var(char **args, t_shell_data *data, int fdin, int fdout)
{
	t_dict	*var;
	int		name_len;
	int		append_mode;
	char	*temp;

	if(fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	while (*args)
	{
		var = ft_calloc_gc(1, sizeof(t_dict));
		append_mode = ft_set_append_mode(*args);
		name_len = ft_strclen(*args, '=');
		var->key = ft_calloc_gc(name_len + 1 - append_mode, sizeof(char));
		ft_strlcpy(var->key, *args, name_len + 1 - append_mode);
		if (append_mode)
			var->value = ft_getvar(data->vars, data->envp, var->key);
		temp = var->value;
		var->value = ft_strjoin_gc(var->value, *args + name_len + 1);
		ft_free(temp);
		if (ft_dictmap(data->envp, var->key))
			ft_dictadd(&data->envp, var->key, var->value);
		ft_dictadd(&data->vars, var->key, var->value);
		ft_free(var);
		args++;
	}
	return (1);
}
