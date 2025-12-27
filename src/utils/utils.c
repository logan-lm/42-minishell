/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:31:12 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/27 11:32:02 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_path(char *path, t_list *envp)
{
	char	*parsed_path;
	char	*pwd;

	if (!path)
		return (path);
	if (*path == '~')
	{
		parsed_path = ft_strjoin_gc(ft_getenv(envp, "HOME"), path + 1);
		ft_free(path);
	}
	else if (*path != '/')
	{
		pwd = ft_dictmap(envp, "PWD");
		if (pwd[ft_strlen(pwd) - 1] == '/')
			parsed_path = ft_strjoin_gc(pwd, path);
		else
			parsed_path = ft_strjoin_mult_gc(3, pwd, "/", path);
		ft_free(path);
	}
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

char	*ft_getvar(t_list *vars, t_list *envp, char *key)
{
	char	*value;

	if (!key)
		return ("");
	value = ft_dictmap(vars, key);
	if (!value)
		value = ft_dictmap(envp, key);
	if (!value)
		return ("");
	return (value);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}
