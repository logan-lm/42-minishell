/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:36:46 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 19:15:37 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export_noarg(t_shell_data *data, int fdout)
{
	t_list	*iterator;
	char	*str;
	t_dict	*var;

	iterator = data->envp;
	while (iterator)
	{
		var = iterator->content;
		str = ft_strjoin_mult_gc_id(malloc_id_exec, 4, var->key, "=\'",
				var->value, "\'\n");
		ft_putstr_fd(str, fdout);
		iterator = iterator->next;
	}
}
