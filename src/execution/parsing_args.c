/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:52:42 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/03 22:19:12 by lomartin         ###   ########.fr       */
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
		free(src);
		return (dest);
	}
	varname_len = ft_strlen(varname);
	*word += varname_len;
	dest = ft_strjoin_gc(src, ft_getvar(data->vars, data->envp, varname));
	free(src);
	free(varname);
	return (dest);
}

void	ft_append_followingpath(t_list *filenames, char *word)
{
	char	*post_wildcard;
	char	*temp;

	post_wildcard = ft_strchr(word, '*') + 1;
	while (filenames)
	{
		temp = filenames->content;
		filenames->content = ft_strjoin_gc(filenames->content, post_wildcard);
		ft_free(temp);
		filenames = filenames->next;
	}
}

size_t	ft_pathsizebeforewildcard(char *word)
{
	size_t	len;
	size_t	i;

	len = ft_strclen(word, '/') + 1;
	i = -1;
	while (word[len + ++i])
	{
		if (word[len + i] == '*')
			return (len);
		if (word[len + i] == '/')
		{
			len += i + 1;
			i = -1;
		}
	}
	return (0);
}

t_list	*ft_expand_wildcard(char *word, t_shell_data *data)
{
	size_t	path_len;
	char	*path;
	t_list	*filenames;
	int		dir;

	if (!data->wc_path)
		data->wc_path = ft_strdup_gc(word);
	path_len = 0;
	if (ft_strhasc(word, '/'))
		path_len = ft_pathsizebeforewildcard(word);
	path = ft_malloc(path_len + 1);
	ft_strlcpy(path, word, path_len + 1);
	dir = ft_strhasc(ft_strchr(word, '*'), '/');
	filenames = ft_get_sorted_dircontent(path, dir);
	if (!filenames)
		return (NULL);
	ft_free(path);
	if (dir)
		ft_append_followingpath(filenames, word);
	return (filenames);
}

t_list	*ft_check_wildcards(t_list *args, t_shell_data *data)
{
	t_list	*curr;
	t_list	*next;
	char	*arg;
	int		i;

	curr = args;
	while (curr)
	{
		arg = curr->content;
		next = curr->next;
		i = -1;
		while (arg[++i])
		{
			if (arg[i] == '*')
			{
				curr->next = ft_expand_wildcard(arg, data);
				if (!curr->next)
					return (args);
				ft_lstlast(curr->next)->next = next;
				ft_lstdelone_fr_gc(&args, curr, ft_free);
				next = args;
				break ;
			}
		}
		curr = next;
	}
	return (args);
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
	dest = malloc((len + 1) * sizeof(char));
	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	free(src);
	ft_strlcpy(dest + i, *word, (len + 1) - i);
	*word += len - i;
	return (dest);
}

t_list	*ft_wordtostr(char *word, t_list **src, t_shell_data *data)
{
	char	**splitted;
	int		i;

	while (*word)
	{
		if (*word == '$' && (!*(word + 1) || (ft_isalpha(*(word + 1)) || *(word
					+ 1) == '?')))
		{
			i = -1;
			splitted = ft_split_gc(ft_expand_var(&word, ft_lstlast(*src)->content, data), ' ');
			ft_lstdelone_fr_gc(src, ft_lstlast(*src), NULL);
			while (splitted[++i])
				ft_lstadd_back(src, ft_lstnew_gc(splitted[i]));
			free(splitted);
			continue ;
		}
		ft_lstlast(*src)->content = ft_copy_nonspecial(&word, ft_lstlast(*src)->content);
	}
	return (*src);
}
