/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_compound_always_checkers.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:00:44 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 07:42:23 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_cmpd_always_expanded(t_string_compound_lst *cmpd)
{
	while (cmpd)
	{
		if (!cmpd->is_expanded)
			return (0);
		cmpd = cmpd->next;
	}
	return (1);
}

int	ft_is_cmpd_always_naked(t_string_compound_lst *cmpd)
{
	while (cmpd)
	{
		if (!cmpd->is_naked)
			return (0);
		cmpd = cmpd->next;
	}
	return (1);
}

int	ft_is_cmpd_always_empty(t_string_compound_lst *cmpd)
{
	while (cmpd)
	{
		if (ft_strcmp("", cmpd->str))
			return (0);
		cmpd = cmpd->next;
	}
	return (1);
}
