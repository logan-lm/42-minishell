/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:36:19 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 09:33:44 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_gc_debug(char *str)
{
	if (ft_strcmp(str, "p0") == 0)
		ft_gc_print_count_id(0);
	if (ft_strcmp(str, "p1") == 0)
		ft_gc_print_count_id(1);
	if (ft_strcmp(str, "p2") == 0)
		ft_gc_print_count_id(2);
	if (ft_strcmp(str, "p3") == 0)
		ft_gc_print_count_id(3);
	if (ft_strcmp(str, "p4") == 0)
		ft_gc_print_count_id(4);
}

void	ft_print_parsed_args(t_list *args)
{
	while (args)
	{
		printf("ARG[%s]\n", (char *)args->content);
		args = args->next;
	}
}
