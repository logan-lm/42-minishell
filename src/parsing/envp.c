/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:41:16 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/12 18:23:52 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_envp(char **envp, t_list **envp_list)
{
	char		**part;
	t_envp_var	*var;
	t_list		*elem;

	while (*envp)
	{
		var = ft_malloc(sizeof(var));
		part = ft_split_gc(*envp, '=');
		var->name = part[0];
		var->value = part[1];
		elem = ft_lstnew_gc(var);
		ft_lstadd_front(envp_list, elem);
		envp++;
	}
}
