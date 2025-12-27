/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:libft/src/ft_lstmerge.c
/*   Created: 2025/12/27 13:55:10 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/27 14:10:28 by lomartin         ###   ########.fr       */
========
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/26 11:42:58 by pberne           ###   ########.fr       */
>>>>>>>> main:src/execution/exec.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<<< HEAD:libft/src/ft_lstmerge.c
t_list	*ft_lstmerge(t_list *dest, t_list *src)
{
	while (src)
	{
		ft_lstadd_back(&dest, src);
		src = src->next;
	}
	return (dest);
}
========


// void	ft_exec(t_list *cmds, t_shell_data *d)
// {
// 	// t_list			*top;
// 	// t_command_node	*cmd;

// 	// top = cmds;
// 	// while (*top)
// 	// {
// 	// 	cmd = top->content;
// 	// 	if (cmd->type == command_pipeline)
// 	// 	top = top->next;
// 	// }
// }
>>>>>>>> main:src/execution/exec.c
