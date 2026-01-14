/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:25:46 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 09:18:38 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Returns the content of an element of a list corresponding to the
/// given key or NULL
/// @param list List in which look for the element
/// @param key Key to look for
/// @param id Malloc id
/// @return Duplicated str of the found element or NULL if not found
char	*ft_dictmap_gc_id(t_list *list, char *key, int id)
{
	size_t	key_len;
	t_dict	*elem;

	key_len = ft_strlen(key);
	while (list)
	{
		elem = list->content;
		if (!ft_strncmp(elem->key, key, key_len + 1))
			return (ft_strdup_gc_id(elem->value, id));
		list = list->next;
	}
	return (NULL);
}

/// @brief Returns the content of an element of a list corresponding to the
/// given key or NULL
///
///default to gc id 0
/// @param list List in which look for the element
/// @param key Key to look for
/// @return Duplicated str of the found element or NULL if not found
char	*ft_dictmap(t_list *list, char *key)
{
	return (ft_dictmap_gc_id(list, key, 0));
}
