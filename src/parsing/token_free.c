/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:11:32 by pberne            #+#    #+#             */
/*   Updated: 2025/12/21 16:31:13 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	ft_free_literal_compound(t_string_compound_lst *lst)
{
	t_string_compound_lst	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		ft_free(temp->str);
		ft_free(temp);
	}
}

void	ft_free_token(t_list *node)
{
	t_parsing_token	*token;
	t_token_op_data	*op_data;

	token = (t_parsing_token *)node->content;
	if (token->type == token_end)
		ft_free(node->content);
	else if (token->type == token_op)
	{
		op_data = (t_token_op_data *)token->data;
		if (op_data->type >= op_in_redirect
			&& op_data->type <= op_out_redirect_append)
			ft_free_literal_compound((t_string_compound_lst *)op_data->word);
		ft_free(token->data);
		ft_free(node->content);
	}
	else
	{
		ft_free_literal_compound((t_string_compound_lst *)token->data);
		ft_free(node->content);
	}
	ft_free(node);
}

void	ft_free_token_list(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		ft_free_token(temp);
	}
}
