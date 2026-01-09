/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:24:08 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/09 16:33:39 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lsttostrs(t_list *lst)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_malloc_id((ft_lstsize(lst) + 1) * (sizeof(char *)),
			malloc_id_exec);
	while (lst)
	{
		strs[i] = lst->content;
		lst = lst->next;
		++i;
	}
	strs[i] = NULL;
	return (strs);
}

char	*ft_getvarname(char *str)
{
	int		len;
	char	*varname;

	len = 1;
	if (*str == '?')
		len = 1;
	else if(*str == '_' || ft_isalpha(*str))
	{
		while (ft_isalnum(str[++len]) || str[len] == '_')
			continue ;
	}
	varname = ft_malloc_id((len + 1) * sizeof(char), malloc_id_exec);
	ft_strlcpy(varname, str, len + 1);
	return (varname);
}

int	ft_ispath(char *str)
{
	while (*str)
	{
		if (*(str++) == '/')
			return (1);
	}
	return (0);
}

int	ft_is_varset(char *cmd)
{
	if (!ft_isalpha(*cmd) && *(cmd + 1))
		return (0);
	cmd++;
	while (*cmd)
	{
		if (*cmd == '=' || (*cmd == '+' && *(cmd + 1) == '='))
			return (1);
		if (!ft_isalnum(*cmd))
			return (0);
		cmd++;
	}
	return (0);
}

char	ft_isdir(char *path)
{
	struct stat	path_stat;

	if (!path)
		return (0);
	ft_bzero(&path_stat, sizeof(path_stat));
	stat(path, &path_stat);
	if (!S_ISDIR(path_stat.st_mode))
	{
		errno = 20;
		return (0);
	}
	return (1);
}
