/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:25:46 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/13 12:11:23 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dictmap(t_list *list, char *key)
{
	int		i;
	size_t	key_len;
	t_dict	*elem;

	i = 0;
	key_len = ft_strlen(key);
	while (list)
	{
		elem = list->content;
		if (!ft_strncmp(elem->key, key, key_len + 1))
			return (elem->value);
		list = list->next;
	}
	return (NULL);
}

/// @brief deletes the entry with a matching key if existing and returns it
/// @param list List in which we want to delete a mode
/// @param key key of the node to delete
/// @return 
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
		((t_dict *)cpy->content)->value = value;
	}
	else
	{
		elem = ft_malloc(sizeof(t_dict));
		elem->key = key;
		elem->value = value;
		ft_lstadd_front(list, ft_lstnew(elem));
	}
}
