/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:11 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/28 18:09:01 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

typedef struct s_command
{
	char	**args;
	int		fdin;
	int		fdout;
}			t_command;

int			ft_parse_fdin(t_list *nodes, t_shell_data *d);
int			ft_parse_fdout(t_list *nodes, t_shell_data *d);
int			ft_has_pipe(t_list *nodes);
t_list		*ft_next_cmd(t_list *nodes);
int			ft_and(t_command_node *command_tree, t_shell_data *data);
int			ft_or(t_command_node *command_tree, t_shell_data *data);
int			ft_subshell(t_command_node *command_tree, t_shell_data *data);

#endif
