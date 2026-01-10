/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 15:25:04 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 19:18:54 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_VAR_H
# define SET_VAR_H

# include "minishell.h"

typedef struct s_set_vars_data
{
	t_dict	*var;
	int		n_l;
	int		a_m;
	char	*temp;
	int		i;
}			t_set_vars_data;

#endif
