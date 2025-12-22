/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/22 15:20:57 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"

void	ft_exec(t_list *cmds, t_shell_data *d)
{
	t_list			*top;
	t_command_node	*cmd;

	top = cmds;
	while (*top)
	{
		cmd = top->content;
		if (cmd->type == command_pipeline)
		top = top->next;
	}
}
