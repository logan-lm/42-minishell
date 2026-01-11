/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:41:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 15:06:53 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_envp(char **av, char **envp, t_shell_data *data)
{
	char	**part;
	char	*pwd;

	data->argv = av;
	data->progname = ft_strrchr(*av, '/');
	data->interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	if (data->progname)
		data->progname++;
	else
		data->progname = *av;
	while (*envp)
	{
		part = ft_split_gc(*envp, '=');
		ft_dictadd(&data->envp, part[0], ft_strchr(*envp, '=') + 1);
		ft_free_strs(part);
		envp++;
	}
	pwd = getcwd(NULL, 0);
	ft_add_exit(pwd, free);
	ft_dictadd(&data->envp, "PWD", pwd);
	ft_dictadd(&data->vars, "?", "0");
	data->lines = 0;
}

/// @brief Exports env dict as char **
/// @param envp_d t_list of the envp dictionnary
/// @return allocated str array
char	**ft_str_env(t_list *envp_d)
{
	int		lst_len;
	char	**envp;
	int		i;
	t_dict	*elem;

	lst_len = ft_lstsize(envp_d);
	envp = ft_malloc_id((lst_len + 1) * sizeof(char *), malloc_id_exec);
	i = -1;
	while (++i < lst_len)
	{
		elem = envp_d->content;
		if (elem->value)
			envp[i] = ft_strjoin_mult_gc_id(malloc_id_exec, 3, elem->key, "=",
					elem->value);
		else
			envp[i] = ft_strjoin_gc_id(elem->key, "=", malloc_id_exec);
		envp_d = envp_d->next;
	}
	envp[i] = NULL;
	return (envp);
}
