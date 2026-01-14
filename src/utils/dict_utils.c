/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:25:46 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 09:38:40 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dict_entry(void *entry)
{
	ft_free(((t_dict *)entry)->key);
	ft_free(((t_dict *)entry)->value);
	ft_free(entry);
}

/// @brief deletes the entry with a matching key if existing and returns it
/// @param list List in which we want to delete a mode
/// @param key key of the node to delete
/// @return Found element (to free) or NULL if not found
t_dict	*ft_dictpop(t_list **list, char *key)
{
	size_t	key_len;
	t_list	*cpy;
	t_dict	*elem;

	key_len = ft_strlen(key);
	cpy = *list;
	while (cpy)
	{
		elem = cpy->content;
		if (!ft_strncmp(elem->key, key, key_len + 1))
		{
			ft_lstdelone_fr(list, cpy, 0);
			return (elem);
		}
		cpy = cpy->next;
	}
	return (NULL);
}

/// @brief Deletes a dict entry corresponging to the given key
/// @param list Dict in zhich delete an entry
/// @param key Key of the entry to delete
void	ft_dictdel(t_list **list, char *key)
{
	size_t	key_len;
	t_list	*cpy;
	t_dict	*elem;

	key_len = ft_strlen(key);
	cpy = *list;
	while (cpy)
	{
		elem = cpy->content;
		if (!ft_strncmp(elem->key, key, key_len + 1))
		{
			ft_lstdelone_fr_gc(list, cpy, free_dict_entry);
			return ;
		}
		cpy = cpy->next;
	}
}

/// @brief Adds an entry to a dict or replaces its value if existing
/// @param list The list formatted as a dictionary
/// @param key Unique key of the new element
/// @param value Value of the new element
void	ft_dictadd(t_list **list, char *key, char *value)
{
	size_t	key_len;
	t_list	*cpy;
	t_dict	*elem;

	key_len = ft_strlen(key);
	cpy = *list;
	while (cpy)
	{
		elem = cpy->content;
		if (!ft_strncmp(elem->key, key, key_len + 1))
			break ;
		cpy = cpy->next;
	}
	if (cpy)
	{
		ft_free(((t_dict *)cpy->content)->value);
		((t_dict *)cpy->content)->value = ft_strdup_gc(value);
	}
	else
	{
		elem = ft_malloc(sizeof(t_dict));
		elem->key = ft_strdup_gc(key);
		elem->value = ft_strdup_gc(value);
		ft_lstadd_front(list, ft_lstnew_gc(elem));
	}
}
