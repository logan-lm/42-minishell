/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:13:32 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/29 10:14:18 by lomartin         ###   ########.fr       */
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

t_list *ft_next_cmd(t_list *nodes)
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
				return (nodes->next);
		}
		nodes = nodes->next;
	}
	return (NULL);
}
