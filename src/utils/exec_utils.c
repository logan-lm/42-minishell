/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:24:08 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 10:03:05 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lsttostrs(t_list *lst)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_malloc((ft_lstsize(lst) + 1) * (sizeof(char *)));
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

	len = 0;
	while (ft_isalnum(str[++len]))
		continue ;
	varname = ft_malloc((len + 1) * sizeof(char));
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
