/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:04:24 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/28 11:06:48 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	ft_join_parts(char **parts, t_dict *var)
{
	char	*temp;
	int		i;

	i = 0;
	while (parts[++i])
	{
		temp = ft_strjoin_gc(var->value, parts[i]);
		ft_free(var->value);
		ft_free(parts[i]);
		var->value = temp;
		if (parts[i + 1])
		{
			temp = ft_strjoin_gc(var->value, "=");
			free(var->value);
			var->value = temp;
		}
	}
} */

int	ft_set_append_mode(char *varname)
{
	size_t	varname_len;

	varname_len = ft_strlen(varname);
	if (varname_len > 0 && varname[varname_len - 2] == '+')
		return (1);
	return (0);
}

int	ft_set_var(char **args, t_shell_data *data, int fdout)
{
	t_dict	*var;
	int		val;
	char	*temp;
	int		append_mode;

	if (fdout != STDOUT_FILENO)
		close(fdout);
	while (*args)
	{
		var = ft_calloc_gc(1, sizeof(t_dict));
		append_mode = ft_set_append_mode(*args);
		var->key = ft_calloc_gc(ft_strlen(*args) - append_mode, sizeof(char));
		ft_strlcpy(var->key, *args, ft_strlen(*args) - append_mode);
		val = 1;
		if (append_mode)
			var->value = ft_getvar(data->vars, data->envp, var->key);
		while (*(args + val) && !ft_is_varset(*(args + val)))
		{
			temp = var->value;
			var->value = ft_strjoin_gc(var->value, *(args + val));
			ft_free(temp);
			++val;
		}
		ft_dictadd(&data->vars, var->key, var->value);
		ft_free(var);
		args += val;
	}
	return (1);
}
