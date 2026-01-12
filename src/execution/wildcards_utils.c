/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:17:22 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/12 19:19:43 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	ft_append_followingpath(t_list *filenames, char *word)
{
	char	*post_wildcard;
	char	*temp;

	post_wildcard = ft_strchr(word, '*') + 1;
	post_wildcard = ft_strchr(post_wildcard, '/');
	while (filenames)
	{
		temp = filenames->content;
		filenames->content = ft_strjoin_gc_id(filenames->content, post_wildcard,
				malloc_id_exec);
		ft_free(temp);
		filenames = filenames->next;
	}
}

size_t	ft_pathsizebeforewildcard(char *word)
{
	size_t	len;
	size_t	i;

	i = -1;
	len = 0;
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
		data->wc_path = ft_strdup_gc_id(word, malloc_id_exec);
	path_len = 0;
	if (ft_strhasc(word, '/'))
		path_len = ft_pathsizebeforewildcard(word);
	path = ft_substr_gc_id(word, 0, path_len, malloc_id_exec);
	dir = ft_strhasc(ft_strchr(word, '*'), '/');
	filenames = ft_get_sorted_dircontent(path, dir);
	if (!filenames)
		return (NULL);
	if (dir)
		ft_append_followingpath(filenames, word);
	return (filenames);
}

void	ft_check_wildcard_while(t_list **args, t_shell_data *data,
		t_check_wildcards_data *w_d)
{
	while (w_d->arg[++w_d->i])
	{
		if (w_d->arg[w_d->i] == '*')
		{
			w_d->temp = ft_expand_wildcard(w_d->arg, data);
			if (!w_d->temp)
			{
				if (ft_lstsize(*args) > 1)
					ft_lstdelone_fr_gc(args, w_d->curr, NULL);
				break ;
			}
			w_d->curr->next = w_d->temp;
			ft_lstlast(w_d->curr->next)->next = w_d->next;
			ft_lstdelone_fr_gc(args, w_d->curr, NULL);
			w_d->next = w_d->temp;
			break ;
		}
	}
}

t_list	*ft_check_wildcards(t_list *args, t_shell_data *data)
{
	t_check_wildcards_data	w_d;

	if (!args)
		return (args);
	ft_bzero(&w_d, sizeof(w_d));
	w_d.curr = args;
	while (w_d.curr)
	{
		w_d.arg = w_d.curr->content;
		w_d.next = w_d.curr->next;
		w_d.i = -1;
		ft_check_wildcard_while(&args, data, &w_d);
		w_d.curr = w_d.next;
	}
	return (args);
}
