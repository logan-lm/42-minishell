/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:52:42 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/12 16:19:59 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

char	**ft_join_strs(char *str, char **strs, char *var)
{
	size_t	strs_len;
	size_t	i;
	size_t	j;
	char	**dest;

	strs_len = -1;
	while (strs[++strs_len])
		;
	if (str && *str && ((var && ft_isspace(*var)) || !var))
		++strs_len;
	dest = ft_malloc_id((strs_len + 1) * sizeof(char *), malloc_id_exec);
	dest[strs_len] = NULL;
	i = -1;
	if (str && *str && ((var && ft_isspace(*var)) || !var))
		dest[++i] = str;
	else
		strs[0] = ft_strjoin_gc_id(str, strs[0], malloc_id_exec);
	j = -1;
	while (strs[++j])
		dest[++i] = strs[j];
	ft_free(strs);
	return (dest);
}

char	**ft_expand_var(char **word, char *src, t_shell_data *data,
		int no_expand)
{
	size_t	varname_len;
	char	*varname;
	char	**dest;

	dest = ft_malloc_id(sizeof(char *) * 2, malloc_id_exec);
	dest[0] = ft_strdup_gc_id(src, malloc_id_exec);
	dest[1] = NULL;
	*word += 1;
	varname = ft_getvarname(*word);
	varname_len = ft_strlen(varname);
	if (!*varname && no_expand && !*word[varname_len])
		return (dest);
	if (!*varname || (!ft_isalnum(*varname) && *varname != '?'))
	{
		dest[0] = ft_strjoin_gc_id(src, "$", malloc_id_exec);
		return (dest);
	}
	ft_free_strs(dest);
	*word += varname_len;
	dest = ft_split_gc_id(ft_getvar(data->vars, data->envp, data->argv,
				varname), ' ', malloc_id_exec);
	// dest[0] = ft_strjoin_gc_id(src, dest[0], malloc_id_exec);
	dest = ft_join_strs(src, dest, ft_getvar(data->vars, data->envp, data->argv,
				varname));
	// ft_free(src);
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
	dest = ft_malloc_id((len + 1) * sizeof(char), malloc_id_exec);
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

void	ft_wordtostr_expand(char **word, t_list **src, t_shell_data *data,
		t_wordtostr_data *w_d)
{
	t_list	*elem;
	char	*str;

	str = NULL;
	elem = ft_lstlast(*src);
	if (elem)
		str = elem->content;
	w_d->i = -1;
	w_d->splitted = ft_expand_var(word, str, data, w_d->no_expand);
	if (w_d->splitted[0] && !*w_d->splitted[0] && !w_d->splitted[1])
		w_d->splitted[0] = NULL;
	if (data->wc_path)
	{
		w_d->temp = data->wc_path;
		data->wc_path = ft_strjoin(data->wc_path, w_d->splitted[w_d->i++]);
		free(w_d->temp);
	}
	else
		ft_lstdelone_fr_gc(src, ft_lstlast(*src), NULL);
	while (w_d->splitted[++w_d->i])
		ft_lstadd_back(src, ft_lstnew_gc_id(w_d->splitted[w_d->i],
				malloc_id_exec));
	ft_free(w_d->splitted);
}

void	ft_wordtostr_wildcards(t_wordtostr_data *w_d, char **word,
		t_shell_data *data)
{
	w_d->temp = data->wc_path;
	w_d->arg = ft_copy_nonspecial(word, w_d->last->content);
	data->wc_path = ft_strjoin_gc_id(data->wc_path, ft_strchr(w_d->arg, '/'),
			malloc_id_exec);
	ft_free(w_d->temp);
	w_d->last->content = w_d->arg;
}

t_list	*ft_wordtostr(char *word, t_list **src, t_shell_data *data,
		int no_expand)
{
	t_wordtostr_data	w_d;

	w_d.no_expand = no_expand;
	while (*word)
	{
		ft_save_src(src);
		if (*word == '$')
		{
			ft_wordtostr_expand(&word, src, data, &w_d);
			continue ;
		}
		w_d.last = ft_lstlast(*src);
		if (*word == '~')
		{
			word++;
			w_d.last->content = ft_strjoin_gc_id(w_d.last->content,
					ft_getenv(data->envp, "HOME"), malloc_id_exec);
			continue ;
		}
		if (data->wc_path)
			ft_wordtostr_wildcards(&w_d, &word, data);
		else
			w_d.last->content = ft_copy_nonspecial(&word, w_d.last->content);
	}
	return (*src);
}
