/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:20:04 by pberne            #+#    #+#             */
/*   Updated: 2025/12/26 11:50:14 by pberne           ###   ########.fr       */
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


/// PIPELINE :
/// commands contains a t_parsing_tokens list
/// (word, redirections, pipes, subshell), the pipeline content
/// if a soken of a pipeline is of type subshell, its data
/// will be a t_command_node * of type subshell.
/// Tis is a terminal operation, left and right are always NULL,
/// nothing can follow a pipe
///
/// SUBSHELL :
/// commands is NULL, the content is always a single command assigned to left
///
/// OR / || :
/// Both left and right contain a command.
/// commands is NULL
typedef struct s_command_node
{
	t_command_node_type		type;
	t_list					*commands;
	struct s_command_node	*left;
	struct s_command_node	*right;
}							t_command_node;

t_command_node				*ft_build_ast(t_list *tokens);
void						ft_print_ast(t_command_node *node, int level);
void						ft_print_ast_visual(t_command_node *node,
								char *prefix);

#endif