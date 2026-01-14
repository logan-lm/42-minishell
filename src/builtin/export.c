/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:36:46 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 09:48:33 by pberne           ###   ########.fr       */
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
	t_dict	entry;

	ft_export_setup(fdin, fdout, &i_ret, &args);
	if (!args[i_ret.x + 1])
		ft_print_export_noarg(data, fdout);
	while (args[++i_ret.x])
	{
		if (!ft_is_varname_valid(args[i_ret.x], data->progname, &i_ret))
			continue ;
		set_mode = ft_strhasequal(args[i_ret.x]);
		append_mode = ft_set_append_mode(args[i_ret.x]);
		entry.key = ft_substr_gc_id(args[i_ret.x], 0, ft_strclen(args[i_ret.x],
					'=') - append_mode, malloc_id_exec);
		if (set_mode)
			ft_set_var((char *[2]){args[i_ret.x], NULL}, data, fdin, fdout);
		entry.value = ft_dictmap_gc_id(data->vars, entry.key, malloc_id_exec);
		if (!entry.value)
			ft_free(entry.key);
		else
			ft_dictadd(&data->envp, entry.key, entry.value);
	}
	return (i_ret.y);
}
