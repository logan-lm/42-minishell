/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:03:31 by pberne            #+#    #+#             */
/*   Updated: 2025/12/21 17:51:38 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	ft_print_lst(t_string_compound_lst *lst)
{
	while (lst)
	{
		ft_printf("\t%d:%s\n", lst->type, lst->str);
		lst = lst->next;
	}
}

void	ft_print_token(t_list *token_lst)
{
	t_parsing_token	*parsing_token;
	int				op_type;

	while (token_lst)
	{
		parsing_token = (t_parsing_token *)token_lst->content;
		if (parsing_token->type == token_end)
			ft_printf("[end]\n");
		else if (parsing_token->type == token_op)
		{
			op_type = ((t_token_op_data *)parsing_token->data)->type;
			ft_printf("[operator: %d]\n", op_type);
			if (op_type >= op_in_redirect && op_type <= op_out_redirect_append)
				ft_print_lst(((t_token_op_data *)parsing_token->data)->word);
		}
		else if (parsing_token->type == token_word)
		{
			ft_printf("[word]\n");
			ft_print_lst((t_string_compound_lst *)parsing_token->data);
		}
		token_lst = token_lst->next;
	}
}
