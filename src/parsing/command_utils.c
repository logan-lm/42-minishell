/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 11:16:51 by pberne            #+#    #+#             */
/*   Updated: 2025/12/24 16:25:39 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_token_ast(t_list *token_lst, int depth)
{
	t_parsing_token	*parsing_token;

	while (token_lst)
	{
		parsing_token = (t_parsing_token *)token_lst->content;
		if (parsing_token->type == token_end)
		{
			ft_print_offset(depth);
			ft_printf("[end]\n");
		}
		else if (parsing_token->type == token_op)
			ft_print_token_op(parsing_token, depth);
		else if (parsing_token->type == token_word)
			ft_print_token_word(parsing_token, depth);
		else if (parsing_token->type == token_subshell)
		{
			ft_print_offset(depth);
			ft_printf("[subshell]\n");
			ft_print_ast((t_command_node *)parsing_token->data, depth + 1);
		}
		token_lst = token_lst->next;
	}
}

void	ft_print_ast(t_command_node *node, int depth)
{
	if (!node)
		return ;
	ft_print_offset(depth);
	if (node->type == command_and || node->type == command_or)
	{
		if(node->type == command_and)
				ft_printf("AND &&:\n");
		else
				ft_printf("OR ||:\n");
		ft_print_ast(node->left, depth + 1);
		ft_print_ast(node->right, depth + 1);
	}
	else if (node->type == command_pipeline)
	{
		ft_printf("PIPELINE:\n");
		ft_print_token_ast(node->commands, depth + 1);
	}
}
