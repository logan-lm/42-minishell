/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:11:32 by pberne            #+#    #+#             */
/*   Updated: 2025/12/17 18:04:57 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	ft_free_literal_compound(t_string_compound_lst *lst)
{
	t_string_compound_lst			*temp;

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

	token = (t_parsing_token *)node->content;
	if (token->type == token_end)
		ft_free(node->content);
	else if (token->type == token_op)
	{
		ft_free(token->data);
		ft_free(node->content);
	}
	else
	{
		ft_free_literal_compound((t_string_compound_lst *)token->data);
		ft_free(node->content);
	}
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
