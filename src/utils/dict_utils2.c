/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:25:46 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 18:01:25 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_dict_keys(t_list *a, t_list *b)
{
	return (ft_strcmp(((t_dict *)a->content)->key,
			((t_dict *)b->content)->key));
}

void	ft_dict_insert_key_ascii(t_list **list, t_list *new_elem)
{
	t_list	*temp;
	t_list	*prev;

	prev = 0;
	temp = *list;
	while (temp)
	{
		if (ft_strcmp_dict_keys(temp, new_elem) <= 0)
		{
			if (prev == 0)
			{
				new_elem->next = temp;
				*list = new_elem;
			}
			else
			{
				prev->next = new_elem;
				new_elem->next = temp;
			}
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
	prev->next = new_elem;
}
