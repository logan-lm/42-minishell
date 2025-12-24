/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:16:51 by pberne            #+#    #+#             */
/*   Updated: 2025/12/24 11:48:58 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_ast(t_command_node *node, int depth)
{
	if (!node)
		return ;
	ft_print_offset(depth);
	if (node->type == command_and)
		ft_printf("AND &&:\n");
	else if (node->type == command_or)
		ft_printf("OR &&:\n");
	else if (node->type == command_subshell)
		ft_printf("SUBSHELL:\n");
	else if (node->type == command_pipeline)
	{
		ft_printf("PIPELINE:\n");
		ft_print_token(node->tokens, depth + 1);
	}
	if (node->type == command_subshell)
		ft_print_ast(node->left, depth + 1);
	else
	{
		ft_print_ast(node->left, depth + 1);
		ft_print_ast(node->right, depth + 1);
	}
}
