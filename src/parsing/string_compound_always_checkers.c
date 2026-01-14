/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_compound_always_checkers.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:00:44 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 11:11:17 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/// @brief Return true if the cmpd has at least one expanded node
int	ft_is_cmpd_expanded_somewhere(t_string_compound_lst *cmpd)
{
	while (cmpd)
	{
		if (cmpd->is_expanded)
			return (1);
		cmpd = cmpd->next;
	}
	return (0);
}

/// @brief Return true if every cmpd node is expanded
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
