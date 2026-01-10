/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:36:46 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 19:15:37 by lomartin         ###   ########.fr       */
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

static void	ft_export_setup(int fdin, int fdout, t_v2i *i_ret, char ***args)
{
	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	i_ret->x = -1;
	i_ret->y = 0;
	*args += 1;
}

int	ft_is_varname_valid(char *str, char *program_name, t_v2i *i_ret)
{
	int		i;
	char	*error;

	i = 0;
	while (str[i] && ft_is_name_character(str[i]))
		i++;
	if (i > 0 && (ft_isalpha(str[0]) || str[0] == '_')
		&& (ft_is_assignement_op(str, &i) || str[i] == '\0'))
		return (1);
	error = ft_strjoin_mult_gc_id(malloc_id_exec, 3, "export: `", str,
			"': not a valid identifier");
	ft_print_error(error, program_name);
	i_ret->y = 1;
	return (0);
}

int	ft_export(char **args, t_shell_data *data, int fdin, int fdout)
{
	t_v2i	i_ret;
	int		set_mode;
	int		append_mode;
	t_dict	var_entry;

	ft_export_setup(fdin, fdout, &i_ret, &args);
	while (args[++i_ret.x])
	{
		if (!ft_is_varname_valid(args[i_ret.x], data->progname, &i_ret))
			continue ;
		set_mode = ft_strhasequal(args[i_ret.x]);
		append_mode = ft_set_append_mode(args[i_ret.x]);
		var_entry.key = ft_substr_gc(args[i_ret.x], 0, ft_strclen(args[i_ret.x],
					'=') - append_mode);
		if (set_mode)
			ft_set_var((char *[2]){args[i_ret.x], NULL}, data, fdin, fdout);
		var_entry.value = ft_dictmap(data->vars, var_entry.key);
		if (!var_entry.value)
			ft_free(var_entry.key);
		else
			ft_dictadd(&data->envp, var_entry.key, var_entry.value);
	}
	return (i_ret.y);
}
