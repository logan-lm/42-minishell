/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:31:12 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 10:45:03 by lomartin         ###   ########.fr       */
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

char	*ft_getenv(t_list *envp, char *key)
{
	char	*value;

	if (!key)
		return ("");
	value = ft_dictmap(envp, key);
	if (!value)
		return ("");
	return (value);
}

char	*ft_try_get_argv(char **args, int n)
{
	int	i;

	i = 0;
	while (args[i] && i < n)
		++i;
	return (args[i]);
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
