/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:43:49 by pberne            #+#    #+#             */
/*   Updated: 2025/12/18 15:03:36 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	ft_add_last_compound_back(void **data, t_string_compound_lst *new_comp)
{
	t_string_compound_lst	*temp;

	if (!*data)
	{
		*data = new_comp;
		return ;
	}
	temp = (t_string_compound_lst *)*data;
	while (temp->next)
		temp = temp->next;
	temp->next = new_comp;
}

void	ft_add_compound_to_back(t_list *token,
		t_string_compound_lst *new_compound)
{
	t_parsing_token	*parsing_tok;

	parsing_tok = (t_parsing_token *)token->content;
	ft_add_last_compound_back(&(parsing_tok->data), new_compound);
}

t_string_compound_lst	*ft_get_string_token_node(char *str, size_t len,
		t_token_word_type word_type)
{
	char					*substr;
	t_string_compound_lst	*str_comp;

	substr = ft_substr_gc(str, 0, len);
	str_comp = ft_malloc(sizeof(t_string_compound_lst));
	str_comp->str = substr;
	str_comp->type = word_type;
	str_comp->next = 0;
	return (str_comp);
}

t_list	*ft_get_word_token(void)
{
	t_parsing_token	*token;

	token = ft_malloc(sizeof(t_parsing_token));
	token->type = token_word;
	token->data = 0;
	return (ft_lstnew_gc(token));
}

/// @brief Iterates through the argument and builds the word compound.
/// the word compound is used to build the real word when it is
/// required
t_list	*ft_get_word(char *str, char **s)
{
	t_list					*token;
	t_string_compound_lst	*new_compound;

	token = ft_get_word_token();
	str = *s;
	while (*str && ft_strchr("|&()<>= \t", *str) == 0)
	{
		if (*str == '\'')
			new_compound = ft_get_word_element_quote(str, s);
		else if (*str == '"')
			new_compound = ft_get_word_element_dquote(str, s);
		else
			new_compound = ft_get_word_element(str, s);
		if (new_compound)
			ft_add_compound_to_back(token, new_compound);
		else
		{
			ft_free_token(token);
			return (0);
		}
		str = *s;
	}
	return (token);
}
