/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:20:04 by pberne            #+#    #+#             */
/*   Updated: 2025/12/25 22:43:57 by pberne           ###   ########.fr       */
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

/// Ici il ne restera que des tokens de pipes, redirection, de words
/// et de subshell.
/// les operateurs && et || ainsi que les parentheses sont remplacees par
/// la structure de l'arbre de commandes.
///
/// PIPELINE :
/// commands contient une liste de t_parsing_tokens
/// (word, redirections, pipes, subshell) definissant le pipeline.
/// si un token est un subshell, sont contenu sera une t_command_node
/// de type command_subshell
/// ceci est une operation finale, left & right
/// sont NULL car rien ne peut suivre un pipe
///
/// SUBSHELL :
/// tokens est vide ici, le contenu du subshell est dans left
/// commands est null
///
/// OR / || :
/// les deux branches left and right contiennent une commande
/// commands est null
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