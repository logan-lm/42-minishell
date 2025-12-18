/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:03:31 by pberne            #+#    #+#             */
/*   Updated: 2025/12/18 12:06:48 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	ft_print_token(t_list *token_lst)
{
	t_parsing_token			*parsing_token;
	t_string_compound_lst	*lst;

	while (token_lst)
	{
		parsing_token = (t_parsing_token *)token_lst->content;
		if (parsing_token->type == token_end)
			ft_printf("[end]\n");
		else if (parsing_token->type == token_op)
		{
			ft_printf("[operator: %d]\n", *((int *)parsing_token->data));
		}
		else if (parsing_token->type == token_literal)
		{
			ft_printf("[literal]\n");
			lst = (t_string_compound_lst *)parsing_token->data;
			while (lst)
			{
				ft_printf("\t%d:%s\n", lst->type, lst->str);
				lst = lst->next;
			}
		}
		token_lst = token_lst->next;
	}
}
