/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validity_checker2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:02:13 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 12:42:12 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

char	*ft_get_fully_bracketed_compound_like_original_token(
			t_string_compound_lst *lst)
{
	char	*dest;
	char	*original_bracket_character;

	dest = "";
	while (lst)
	{
		if (lst->is_naked)
		{
			dest = ft_strjoin_gc_id(dest, lst->str, malloc_id_token);
			lst = lst->next;
			continue ;
		}
		else if (lst->type == word_true)
			original_bracket_character = "'";
		else
			original_bracket_character = "\"";
		dest = ft_strjoin_mult_gc_id(malloc_id_token, 4, dest,
				original_bracket_character, lst->str,
				original_bracket_character);
		lst = lst->next;
	}
	return (dest);
}

int	ft_verify_subshell_pipelines(t_list *token_lst)
{
	int				prevent_words;
	t_token_op_type	tk_t;
	t_parsing_token	*token;

	prevent_words = 0;
	while (token_lst)
	{
		token = token_lst->content;
		if (token->type == token_word && prevent_words)
		{
			return (ft_token_syntax_error(
					ft_get_fully_bracketed_compound_like_original_token(
						token->data)), 0);
		}
		if (token->type == token_op)
		{
			tk_t = ((t_token_op_data *)token->data)->type;
			if (tk_t == op_close_parenthesis)
				prevent_words = 1;
			else if (tk_t == op_pipe || tk_t == op_or || tk_t == op_and)
				prevent_words = 0;
		}
		token_lst = token_lst->next;
	}
	return (1);
}
