/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:13:32 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 17:00:36 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
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

void	ft_next_cmd_norm(t_list *nodes, t_next_cmd_data *n_d)
{
	n_d->token_next = nodes->next->content;
	n_d->op_token_next = n_d->token_next->data;
}

t_list	*ft_next_cmd(t_list *nodes)
{
	t_next_cmd_data	n_d;

	while (nodes)
	{
		n_d.token = nodes->content;
		if (n_d.token->type == token_op)
		{
			n_d.op_token = n_d.token->data;
			if (n_d.op_token->type == op_pipe)
			{
				if (!nodes->next)
					return (nodes->next);
				ft_next_cmd_norm(nodes, &n_d);
				if (n_d.token_next->type == token_op
					&& n_d.op_token_next->type == op_pipe)
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
