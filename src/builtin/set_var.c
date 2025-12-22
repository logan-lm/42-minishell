/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:04:24 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/22 10:42:02 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_join_parts(char **parts, t_dict *var)
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
}

int	ft_set_var(char **args, t_shell_data *data)
{
	t_dict	*var;
	char	**parts;

	while (*args)
	{
		parts = ft_split_gc(*args, '=');
		var = ft_malloc(sizeof(t_dict));
		var->value = NULL;
		var->key = parts[0];
		ft_join_parts(parts, var);
		ft_dictadd(&data->vars, var->key, var->value);
		ft_free(var);
		ft_free(parts);
		args++;
	}
	return (1);
}
