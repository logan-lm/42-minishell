/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:41:16 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/30 22:23:17 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_envp(char **av, char **envp, t_shell_data *data)
{
	char	**part;

	data->progname = ft_strchr(*av, '/');
	if (data->progname)
		data->progname++;
	else
		data->progname = *av;
	while (*envp)
	{
		part = ft_split_gc(*envp, '=');
		ft_dictadd(&data->envp, part[0], part[1]);
		envp++;
	}
	ft_dictadd(&data->envp, "PWD", getcwd(NULL, 0));
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
	envp = ft_malloc((lst_len + 1) * sizeof(char *));
	i = -1;
	while (++i < lst_len)
	{
		elem = envp_d->content;
		if (elem->value)
			envp[i] = ft_strjoin_mult_gc(3, elem->key, "=", elem->value);
		else
			envp[i] = ft_strjoin_gc(elem->key, "=");
		envp_d = envp_d->next;
	}
	envp[i] = NULL;
	return (envp);
}
