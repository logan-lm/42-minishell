/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:20:04 by pberne            #+#    #+#             */
/*   Updated: 2025/12/22 11:18:49 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"
# include "parser.h"

typedef struct s_command_node
{
	t_command_node_type	type;
	t_list				*pipeline;
	t_command_node		*left;
	t_command_node		*right;
}						t_command_node;

typedef enum e_command_node_type
{
	command_pipeline,
	command_or,
	command_and,
	command_subshell
}						t_command_node_type;

#endif