/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:52:42 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 11:17:30 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

char	*ft_expand_var(char **word, char *src, t_shell_data *data)
{
	size_t	varname_len;
	char	*varname;
	char	*dest;

	*word += 1;
	varname = ft_getvarname(*word);
	if (!*varname)
	{
		dest = ft_strjoin(src, "$");
		ft_free(src);
		return (dest);
	}
	varname_len = ft_strlen(varname);
	*word += varname_len;
	dest = ft_strjoin_gc(src, ft_getvar(data->vars, data->envp, varname));
	ft_free(src);
	ft_free(varname);
	return (dest);
}

char	*ft_copy_nonspecial(char **word, char *src)
{
	size_t	i;
	size_t	len;
	char	*dest;

	i = -1;
	len = ft_strlen(src);
	while ((*word)[++i] && (*word)[i] != '$')
		++len;
	dest = ft_malloc((len + 1) * sizeof(char));
	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	ft_free(src);
	ft_strlcpy(dest + i, *word, (len + 1) - i);
	*word += len - i;
	return (dest);
}

t_list	*ft_wordtostr(char *word, t_list **src, t_shell_data *data)
{
	char	**splitted;
	char	*temp;
	char	*arg;
	t_list	*last;
	int		i;

	while (*word)
	{
		if (*word == '$' && (!*(word + 1) || (ft_isalpha(*(word + 1)) || *(word
						+ 1) == '?')))
		{
			i = -1;
			splitted = ft_split_gc(ft_expand_var(&word,
						ft_lstlast(*src)->content, data), ' ');
			if (data->wc_path)
			{
				temp = data->wc_path;
				data->wc_path = ft_strjoin(data->wc_path, splitted[i++]);
				free(temp);
			}
			else
				ft_lstdelone_fr_gc(src, ft_lstlast(*src), NULL);
			while (splitted[++i])
				ft_lstadd_back(src, ft_lstnew_gc(splitted[i]));
			ft_free(splitted);
			continue ;
		}
		last = ft_lstlast(*src);
		if (data->wc_path)
		{
			temp = data->wc_path;
			arg = ft_copy_nonspecial(&word, last->content);
			data->wc_path = ft_strjoin(data->wc_path, ft_strchr(arg, '/'));
			free(temp);
			last->content = arg;
		}
		else
			last->content = ft_copy_nonspecial(&word, last->content);
	}
	return (*src);
}
