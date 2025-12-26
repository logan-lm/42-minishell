/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:19:02 by pberne            #+#    #+#             */
/*   Updated: 2025/12/26 12:05:41 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

/// Looks for the rightmost operator
/// if there is one, split the token list in 2 parts and create the subcommands
/// to the LEFT we send the tokens BEFORE the operator,
/// to the RIGHT we send the tokens AFTER the operator.
/// the operator token is discaded.
/// If there is no operators, there cannot be any more branches,
/// the command is a pipeline. 
/// Then the subshell tokens are converted into commands.

int	ft_is_comparison_op(t_list *token_iterator)
{
	t_parsing_token	*token;

	token = (t_parsing_token *)token_iterator->content;
	if (token->type == token_op)
	{
		if (((t_token_op_data *)token->data)->type == op_or)
			return (command_or);
		else if ((((t_token_op_data *)token->data)->type == op_and))
			return (command_and);
	}
	return (0);
}

int	ft_get_command_type(t_list *token_iterator)
{
	t_parsing_token	*token;

	token = (t_parsing_token *)token_iterator->content;
	if (token->type == token_op)
	{
		if (((t_token_op_data *)token->data)->type == op_or)
			return (command_or);
		else if ((((t_token_op_data *)token->data)->type == op_and))
			return (command_and);
	}
	else if (token->type == token_subshell)
		return (command_subshell);
	return (0);
}

t_list	*ft_get_last_comp_operator(t_list *token_lst, int *command_type,
		int last_command_type, t_list *last_comp_operator)
{
	t_list	*prev;
	t_list	*last_prev;
	int		cmd_type;

	*command_type = 0;
	prev = 0;
	while (token_lst)
	{
		cmd_type = ft_is_comparison_op(token_lst);
		if (cmd_type)
		{
			last_command_type = cmd_type;
			last_prev = prev;
			last_comp_operator = token_lst;
		}
		prev = token_lst;
		token_lst = token_lst->next;
	}
	if (last_command_type)
	{
		last_prev->next = 0;
		*command_type = last_command_type;
	}
	return (last_comp_operator);
}

void	ft_build_subshell_commands_from_tokens(t_list *token_lst)
{
	t_parsing_token	*token;

	while (token_lst)
	{
		token = (t_parsing_token *)token_lst->content;
		if (token->type == token_subshell)
			token->data = ft_build_ast((t_list *)token->data);
		token_lst = token_lst->next;
	}
}

t_command_node	*ft_build_ast(t_list *token_lst)
{
	t_command_node	*new_command;
	t_list			*start;
	int				command_type;

	start = token_lst;
	new_command = ft_malloc_id(sizeof(t_command_node), malloc_id_ast);
	token_lst = ft_get_last_comp_operator(token_lst, &command_type, 0, 0);
	if (command_type)
	{
		new_command->type = command_type;
		new_command->left = ft_build_ast(start);
		new_command->right = ft_build_ast(token_lst->next);
	}
	else
	{
		new_command->type = command_pipeline;
		new_command->commands = start;
		ft_build_subshell_commands_from_tokens(start);
	}
	return (new_command);
}
