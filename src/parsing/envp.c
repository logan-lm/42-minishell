/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:41:16 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/13 12:09:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_envp(char **envp, t_list **envp_list)
{
	char		**part;

	while (*envp)
	{
		part = ft_split_gc(*envp, '=');
		ft_dictadd(envp_list, part[0], part[1]);
		envp++;
	}
}
