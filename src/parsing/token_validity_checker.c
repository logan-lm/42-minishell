/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validity_checker.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:29:30 by pberne            #+#    #+#             */
/*   Updated: 2025/12/22 12:02:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/// @brief Makes sure the parenthesis count is correct,
/// every open parenthesis has a closing on in the correct order
int	ft_token_verify_parenthesis(t_list *token_lst)
{
	int				count;
	t_parsing_token	*token;

	count = 0;
	while (token_lst)
	{
		token = (t_parsing_token *)token_lst->content;
		if (token->type == token_op)
		{
			if (*((int *)token->data) == op_open_parenthesis)
				count += 1;
			else if (*((int *)token->data) == op_close_parenthesis)
				count -= 1;
			if (count < 0)
			{
				ft_token_missing_parenthesis(*((int *)token->data));
				return (0);
			}
		}
		token_lst = token_lst->next;
	}
	if (count > 0)
		ft_token_missing_parenthesis(op_open_parenthesis);
	return (count == 0);
}

void	ft_merge_redirection_token(t_list *token_lst)
{
	t_list					*next;
	t_token_op_data			*op_data;
	t_string_compound_lst	*nword;

	op_data = (t_token_op_data *)((t_parsing_token *)token_lst->content)->data;
	next = token_lst->next;
	nword = (t_string_compound_lst *)((t_parsing_token *)next->content)->data;
	token_lst->next = next->next;
	op_data->word = nword;
	ft_free(next->content);
	ft_free(next);
}

/// @brief Checks if the redirections are properly formatted
///(with a word following them) and merges them
int	ft_token_verify_redirection(t_list *token_lst)
{
	t_parsing_token	*token;
	int				ret;

	while (token_lst)
	{
		token = (t_parsing_token *)token_lst->content;
		if (token->type == token_op)
		{
			ret = ft_is_redirection_valid((t_token_op_type *)token->data,
					(t_parsing_token *)token_lst->next->content);
			if (!ret)
				return (0);
			else if (ret == 2)
				ft_merge_redirection_token(token_lst);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

int	ft_token_verify_operators(t_list *token_lst)
{
	t_parsing_token	*token;
	int				validity_id;

	while (token_lst)
	{
		token = (t_parsing_token *)token_lst->content;
		if (token->type == token_op)
		{
			if (!ft_is_operator_valid((t_token_op_type *)token->data,
					(t_parsing_token *)token_lst->next->content))
				return (0);
			if (validity_id == 2)
				ft_merge_redirection_token(token_lst);
		}
		token_lst = token_lst->next;
	}
	return (1);
}

t_list	*ft_token_validity_checker(t_list *token_lst)
{
	if (!token_lst)
		return (0);
	if (!ft_token_verify_parenthesis(token_lst))
	{
		ft_free_token_list(token_lst);
		return (0);
	}
	if (!ft_token_verify_redirection(token_lst))
	{
		ft_free_token_list(token_lst);
		return (0);
	}
	if (!ft_token_verify_operators(token_lst))
	{
		ft_free_token_list(token_lst);
		return (0);
	}
	return (token_lst);
}
