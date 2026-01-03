/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:52:42 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/02 20:12:38 by lomartin         ###   ########.fr       */
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

t_list	*ft_expand_wildcard(char *word, t_shell_data *data)
{
	size_t	path_len;
	char	*path;
	t_list	*filenames;
	//t_list	*good_filenames;
	int		dir;

	if (!data->wc_path)
		data->wc_path = word;
	path_len = ft_strclen(word, '*');
	path = ft_malloc(path_len + 1);
	ft_strlcpy(path, word, path_len + 1);
	dir = ft_strhasc(ft_strchr(word, '*'), '/');
	filenames = ft_get_sorted_dircontent(path, dir);
	if (!filenames)
		return (NULL);
	ft_free(path);
	/*path = ft_malloc(path_len + 2);
	ft_strlcpy(path, word, path_len + 2);
	good_filenames = ft_get_matching_names(filenames, word);
	ft_free(path);*/
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

char	*ft_wordtostr(char *word, t_shell_data *data)
{
	char	*joined;

	joined = ft_strdup("");
	while (*word)
	{
		if (*word == '$' && (!*(word + 1) || (ft_isalpha(*(word + 1)) || *(word
					+ 1) == '?')))
		{
			joined = ft_expand_var(&word, joined, data);
			continue ;
		}
		joined = ft_copy_nonspecial(&word, joined);
	}
	return (joined);
}
