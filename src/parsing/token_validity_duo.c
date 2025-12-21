/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validity_duo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:55:06 by pberne            #+#    #+#             */
/*   Updated: 2025/12/21 16:37:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_is_token_duo_valid(t_token_op_type *token_type,
		t_parsing_token *next_token)
{
	t_token_op_type	*next_op;

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
	else if (*token_type == op_pipe || *token_type == op_and
		|| *token_type == op_or || *token_type == op_open_parenthesis)
	{
		if (next_token->type == token_end)
			return (ft_token_syntax_error("newline"), 0);
		next_op = (t_token_op_type *)next_token->data;
		if (*next_op == op_pipe || *next_op == op_and || *next_op == op_or)
			return (ft_op_syntax_error(*next_op), 0);
	}
	return (1);
}
