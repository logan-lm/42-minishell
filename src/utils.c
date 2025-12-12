/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:25:46 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/12 18:30:09 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dictmap(char *var, t_list *envp)
{
	int			i;
	size_t		var_len;
	t_dict		*elem;

	i = 0;
	var_len = ft_strlen(var);
	while (envp)
	{
		elem = envp->content;
		if (!ft_strncmp(elem->key, var, var_len + 1))
			return (elem->value);
		envp = envp->next;
	}
	return (NULL);
}

void	ft_dictadd(t_list **list, char *key, char *value)
{

}
