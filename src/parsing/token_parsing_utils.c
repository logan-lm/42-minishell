/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:03:31 by pberne            #+#    #+#             */
/*   Updated: 2025/12/25 23:09:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	ft_print_offset(int i)
{
	while (--i >= 0)
		ft_printf("\t");
}

void	ft_print_lst(t_string_compound_lst *lst, int depth)
{
	while (lst)
	{
		ft_print_offset(depth);
		ft_printf("%d:%s\n", lst->type, lst->str);
		lst = lst->next;
	}
}

void	ft_print_tkn_op(t_parsing_token *parsing_token, int depth)
{
	int	op_type;

	op_type = ((t_token_op_data *)parsing_token->data)->type;
	ft_print_offset(depth);
	ft_printf("[operator: %d]\n", op_type);
	if (op_type >= op_in_redirect && op_type <= op_out_redirect_append)
		ft_print_lst(((t_token_op_data *)parsing_token->data)->word, depth + 1);
}

void	ft_print_tkn_w(t_parsing_token *parsing_token, int depth)
{
	ft_print_offset(depth);
	ft_printf("[word]\n");
	ft_print_lst((t_string_compound_lst *)parsing_token->data, depth + 1);
}

void	ft_print_token(t_list *token_lst, int depth)
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
			ft_print_tkn_op(parsing_token, depth);
		else if (parsing_token->type == token_word)
			ft_print_tkn_w(parsing_token, depth);
		else if (parsing_token->type == token_subshell)
		{
			ft_print_offset(depth);
			ft_printf("[subshell]\n");
			ft_print_token((t_list *)parsing_token->data, depth + 1);
		}
		token_lst = token_lst->next;
	}
}
