/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:24:08 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/27 19:08:28 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lsttostrs(t_list *lst)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_malloc(ft_lstsize(lst) * (sizeof(char *) + 1));
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

char	*ft_wordtostr(char *word, t_shell_data *data)
{
	char	*str;
	int		i;
	int		j;
	char	*temp;

	i = -1;
	j = 0;
	str = NULL;
	while (word[++i] && word[i + 1])
	{
		if (word[i] != '$' || !ft_isalpha(word[i + 1]))
			continue ;
		temp = ft_malloc((i - j + 2) * sizeof(char));
		ft_strlcpy(temp, word + j, i - j + 1);
		str = ft_strjoin_gc(str, temp);
		ft_free(temp);
		j = i + 1;
		temp = ft_getvarname(word + j);
		str = ft_strjoin_gc(str, ft_getvar(data->vars, data->envp, temp));
		j += ft_strlen(temp);
		temp = NULL;
	}
	i++;
	temp = ft_malloc((i - j + 2) * sizeof(char));
	ft_strlcpy(temp, word + j, i - j + 1);
	str = ft_strjoin_gc(str, temp);
	free(temp);
	return (str);
}
