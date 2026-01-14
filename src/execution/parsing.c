/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:38:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 06:38:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_parse_cmd_while(t_parsecmd_data *p_d, t_shell_data *d)
{
	p_d->token = p_d->nodes_cpy->content;
	p_d->op_token = p_d->token->data;
	if (p_d->token->type == token_op)
	{
		if (p_d->op_token->type == op_pipe)
			return (1);
	}
	if (p_d->token->type == token_subshell)
	{
		ft_lstadd_back(&p_d->args_lst, ft_lstnew_gc_id("()", malloc_id_exec));
		ft_lstadd_back(&p_d->args_lst, ft_lstnew_gc_id(p_d->token->data,
				malloc_id_exec));
	}
	if (p_d->token->type == token_word)
		p_d->args_lst = ft_lstmerge_id(p_d->args_lst,
				ft_parse_cmd_args(p_d->token->data, d), malloc_id_exec);
	p_d->nodes_cpy = p_d->nodes_cpy->next;
	return (0);
}

t_list	*ft_parse_cmd(t_list **nodes, t_shell_data *d)
{
	t_parsecmd_data	p_d;

	p_d.args_lst = NULL;
	p_d.nodes_cpy = *nodes;
	while (p_d.nodes_cpy)
	{
		if (ft_parse_cmd_while(&p_d, d) == 1)
			break ;
	}
	return (p_d.args_lst);
}
