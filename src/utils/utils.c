/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:31:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 09:19:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_path(char *path, t_list *envp)
{
	char	*parsed_path;

	if (!path)
		return (path);
	if (*path == '-' && (!path[1] || (path[1] == '-' && !path[2])))
		parsed_path = ft_getenv(envp, "OLDPWD");
	else
		parsed_path = path;
	return (parsed_path);
}

char	*ft_try_get_argv(char **args, int n)
{
	int	i;

	i = 0;
	while (args[i] && i < n)
		++i;
	return (args[i]);
}

char	*ft_getvar_exec(t_list *vars, t_list *envp, char **args, char *key)
{
	char	*value;

	if (!key)
		return (NULL);
	if (ft_isdigit(key[0]))
		return (ft_try_get_argv(args, ft_atoi(key)));
	value = ft_dictmap_gc_id(vars, key, malloc_id_exec);
	if (!value)
		value = ft_dictmap_gc_id(envp, key, malloc_id_exec);
	return (value);
}

char	*ft_getvar(t_list *vars, t_list *envp, char **args, char *key)
{
	char	*value;

	if (!key)
		return (NULL);
	if (ft_isdigit(key[0]))
		return (ft_try_get_argv(args, ft_atoi(key)));
	value = ft_dictmap(vars, key);
	if (!value)
		value = ft_dictmap(envp, key);
	return (value);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		ft_free(strs[i++]);
	ft_free(strs);
}
