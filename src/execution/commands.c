/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:13:32 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 19:19:26 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_pipe(t_list *nodes)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;

	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
				return (1);
		}
		nodes = nodes->next;
	}
	return (0);
}

t_list	*ft_next_cmd(t_list *nodes)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;
	t_parsing_token	*token_next;
	t_token_op_data	*op_token_next;

	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
			{
				if (!nodes->next)
					return (nodes->next);
				token_next = nodes->next->content;
				op_token_next = token_next->data;
				if (token_next->type == token_op
					&& op_token_next->type == op_pipe)
				{
					nodes = nodes->next;
					continue ;
				}
				return (nodes->next);
			}
		}
		nodes = nodes->next;
	}
	return (NULL);
}
