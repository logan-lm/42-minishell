/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:20:18 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 09:20:28 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv_gc_id(t_list *envp, char *key, int id)
{
	char	*value;

	if (!key)
		return ("");
	value = ft_dictmap_gc_id(envp, key, id);
	if (!value)
		return ("");
	return (value);
}

char	*ft_getenv(t_list *envp, char *key)
{
	return (ft_getenv_gc_id(envp, key, 0));
}
