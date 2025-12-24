/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_build_subshells.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 11:29:51 by pberne            #+#    #+#             */
/*   Updated: 2025/12/24 11:43:22 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/// @brief Transforms an open_parenthesis token into a subshell token
/// and injects its content + removes the matching closing parenthesis token
void	ft_subshellize_n(t_list *token_lst, int n)
{
	t_parsing_token	*token;
	t_list			*subshell_node;
	int				i;

	i = 1;
	subshell_node = token_lst;
	token = (t_parsing_token *)token_lst->content;
	token->data = token_lst->next;
	while (i < n)
	{
		token_lst = token_lst->next;
		i++;
	}
	subshell_node->next = token_lst->next->next;
	token_lst->next = 0;
}

/// @brief Removes the parenthesis tokens and replace them with a
/// subshell token containing the data between the parenthesis
void	ft_merge_subshell_r(t_list **iterator, t_list *curr, t_list *prev,
		t_parsing_token *token)
{
	while (*iterator)
	{
		curr = *iterator;
		token = (t_parsing_token *)curr->content;
		if (token->type == token_op
			&& ((t_token_op_data *)token->data)->type == op_open_parenthesis)
		{
			token->type = token_subshell;
			*iterator = curr->next;
			token->data = *iterator;
			ft_merge_subshell_r(iterator, 0, 0, 0);
			curr->next = *iterator;
		}
		else if (token->type == token_op
			&& ((t_token_op_data *)token->data)->type == op_close_parenthesis)
		{
			if (prev)
				prev->next = NULL;
			*iterator = curr->next;
			return ;
		}
		prev = curr;
		*iterator = curr->next;
	}
}

t_list	*ft_merge_subshell_token_lst(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	ft_merge_subshell_r(&tmp, 0, 0, 0);
	return (head);
}
