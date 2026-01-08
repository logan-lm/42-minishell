/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 10:04:24 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/08 15:17:33 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "set_var.h"

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
	t_set_vars_data	s;

	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	s.i = -1;
	while (args[++s.i])
	{
		s.var = ft_calloc_gc(1, sizeof(t_dict));
		s.a_m = ft_set_append_mode(args[s.i]);
		s.n_l = ft_strclen(args[s.i], '=');
		s.var->key = ft_calloc_gc(s.n_l + 1 - s.a_m, sizeof(char));
		ft_strlcpy(s.var->key, args[s.i], s.n_l + 1 - s.a_m);
		if (s.a_m)
			s.var->value = ft_getvar(data->vars, data->envp, s.var->key);
		s.temp = s.var->value;
		s.var->value = ft_strjoin_gc(s.var->value, args[s.i] + s.n_l + 1);
		ft_free(s.temp);
		if (ft_dictmap(data->envp, s.var->key))
			ft_dictadd(&data->envp, s.var->key, s.var->value);
		ft_dictadd(&data->vars, s.var->key, s.var->value);
		ft_free(s.var->value);
		ft_free(s.var);
	}
	return (0);
}
