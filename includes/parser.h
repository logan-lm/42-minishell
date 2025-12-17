/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:23:36 by pberne            #+#    #+#             */
/*   Updated: 2025/12/17 18:41:47 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

/// @brief defines the type of a token
typedef enum e_token_type
{
	token_end,
	token_op,
	token_literal
}									t_token_type;

typedef struct s_parsing_token
{
	t_token_type					type;
	void							*data;
}									t_parsing_token;

/// @brief Defines the type of an operator token
typedef enum e_token_op_type
{
	op_pipe,
	op_in_redirect,
	op_heredoc,
	op_out_redirect_trunc,
	op_out_redirect_append,
	op_open_parenthesis,
	op_close_parenthesis,
	op_and,
	op_or
}									t_token_op_type;

typedef enum e_token_literal_type
{
	literal_true,
	literal_replace_vars
}									t_token_literal_type;

typedef struct s_string_compound_lst
{
	t_token_literal_type			type;
	char							*str;
	struct s_string_compound_lst	*next;

}									t_string_compound_lst;

t_list								*ft_get_tokens(char *str);

void								ft_free_token_list(t_list *lst);
void								ft_free_token(t_list *node);

t_list								*ft_get_op_token(t_token_op_type op_type);

t_list								*ft_get_operator(char *str, char **s);
t_list								*ft_get_literal(char *str, char **s);

t_string_compound_lst				*ft_get_string_token_node(char *str,
										size_t len,
										t_token_literal_type literal_type);
t_string_compound_lst				*ft_get_literal_element(char *str,
										char **s);
t_string_compound_lst				*ft_get_literal_element_quote(char *str,
										char **s);
t_string_compound_lst				*ft_get_literal_element_dquote(char *str,
										char **s);

void								ft_token_syntax_error(char *c);
void								ft_token_missing_delimiter_error(char *c);

#endif