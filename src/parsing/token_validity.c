/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:55:06 by pberne            #+#    #+#             */
/*   Updated: 2026/01/10 20:30:24 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_is_redirection_valid(t_token_op_type *token_type,
		t_parsing_token *next_token)
{
	if (*token_type >= op_in_redirect && *token_type <= op_out_redirect_append)
	{
		if (next_token->type != token_word)
		{
			if (next_token->type == token_op)
				ft_op_syntax_error(*(t_token_op_type *)next_token->data);
			else
				ft_token_syntax_error("newline");
			return (0);
		}
		else
			return (2);
	}
	return (1);
}

int	ft_is_operator_valid2(t_token_op_type *token_type,
		t_parsing_token *next_token)
{
	t_token_op_type	next_op;

	if (*token_type == op_close_parenthesis)
	{
		if (next_token->type == token_op)
		{
			next_op = ((t_token_op_data *)next_token->data)->type;
			if (next_op == op_open_parenthesis)
				return (ft_op_syntax_error(next_op), 0);
		}
	}
	return (1);
}

int	ft_is_operator_valid(t_token_op_type *token_type,
		t_parsing_token *next_token, t_parsing_token *prev_token)
{
	t_token_op_type	next_op;

	if (*token_type == op_pipe || *token_type == op_and || *token_type == op_or
		|| *token_type == op_open_parenthesis)
	{
		if (next_token->type == token_end)
			return (ft_op_syntax_error(*token_type), 0);
		if (*token_type != op_open_parenthesis && prev_token == NULL)
			return (ft_op_syntax_error(*token_type), 0);
		if (next_token->type == token_op)
		{
			next_op = ((t_token_op_data *)next_token->data)->type;
			if (next_op == op_pipe || next_op == op_and || next_op == op_or
				|| next_op == op_close_parenthesis)
			{
				if (*token_type == op_open_parenthesis
					&& next_op == op_close_parenthesis)
					return (ft_op_syntax_error(next_op), 0);
				else
					return (ft_op_syntax_error(*token_type), 0);
			}
		}
	}
	return (ft_is_operator_valid2(token_type, next_token));
}

void	ft_remove_end_token(t_list **token_lst)
{
	t_list	*prev;
	t_list	*iterator;

	prev = 0;
	iterator = *token_lst;
	while (iterator->next)
	{
		prev = iterator;
		iterator = iterator->next;
	}
	if (prev)
		prev->next = 0;
	else
		*token_lst = 0;
}
