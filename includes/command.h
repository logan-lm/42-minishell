/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:20:04 by pberne            #+#    #+#             */
/*   Updated: 2025/12/24 11:49:23 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"
# include "parser.h"

typedef enum e_command_node_type
{
	command_pipeline,
	command_or,
	command_and,
	command_subshell
}							t_command_node_type;

typedef struct s_command_node
{
	t_command_node_type		type;
	t_list					*tokens;
	struct s_command_node	*left;
	struct s_command_node	*right;
}							t_command_node;

t_command_node				*ft_build_ast(t_list *tokens);
void						ft_print_ast(t_command_node *node, int level);

#endif