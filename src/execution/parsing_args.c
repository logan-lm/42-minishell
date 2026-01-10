/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:52:42 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 19:15:51 by lomartin         ###   ########.fr       */
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
	if (!*varname || (!ft_isalnum(*varname) && *varname != '?'))
	{
		dest = ft_strjoin(src, "$");
		ft_free(src);
		return (dest);
	}
	varname_len = ft_strlen(varname);
	*word += varname_len;
	dest = ft_strjoin_gc_id(src, ft_getvar(data->vars, data->envp, data->argv,
				varname), malloc_id_exec);
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

void	ft_wordtostr_expand(char **word, t_list **src, t_shell_data *data,
		t_wordtostr_data *w_d)
{
	w_d->i = -1;
	w_d->splitted = ft_split_gc_id(ft_expand_var(word,
				ft_lstlast(*src)->content, data), ' ', malloc_id_exec);
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

t_list	*ft_wordtostr(char *word, t_list **src, t_shell_data *data)
{
	t_wordtostr_data	w_d;

	while (*word)
	{
		if (*word == '$')
		{
			ft_wordtostr_expand(&word, src, data, &w_d);
			continue ;
		}
		w_d.last = ft_lstlast(*src);
		if (data->wc_path)
		{
			w_d.temp = data->wc_path;
			w_d.arg = ft_copy_nonspecial(&word, w_d.last->content);
			data->wc_path = ft_strjoin_gc_id(data->wc_path, ft_strchr(w_d.arg,
						'/'), malloc_id_exec);
			ft_free(w_d.temp);
			w_d.last->content = w_d.arg;
		}
		else
			w_d.last->content = ft_copy_nonspecial(&word, w_d.last->content);
	}
	return (*src);
}
