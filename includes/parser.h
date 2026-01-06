/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 13:23:36 by pberne            #+#    #+#             */
/*   Updated: 2026/01/06 18:18:41 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

typedef enum e_malloc_id
{
	malloc_id_default,
	malloc_id_token,
	malloc_id_ast,
	malloc_id_exec
}								t_malloc_id;

/// @brief defines the type of a token
typedef enum e_token_type
{
	token_end,
	token_op,
	token_word,
	token_subshell
}								t_token_type;

typedef struct s_parsing_token
{
	t_token_type				type;
	void						*data;
}								t_parsing_token;

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
	op_or,
}								t_token_op_type;

typedef enum e_token_word_type
{
	word_true,
	word_replace_vars,
}								t_token_word_type;

typedef struct s_string_cmpd_lst
{
	t_token_word_type			type;
	int							is_name;
	char						*str;
	struct s_string_cmpd_lst	*next;

}								t_string_compound_lst;

typedef struct s_token_op_data
{
	t_token_op_type				type;
	t_string_compound_lst		*word;
}								t_token_op_data;

// Token

t_list							*ft_get_tokens(char *str);
void							ft_free_token_list(t_list *lst);
void							ft_free_token(t_list *node);

t_list							*ft_get_op_token(t_token_op_type op_type);
t_list							*ft_get_operator(char *str, char **s);

t_list							*ft_merge_subshell_token_lst(t_list *iterator);

// Word

t_list							*ft_get_word(char *str, char **s);
t_string_compound_lst			*ft_build_word_token(char *str);
t_string_compound_lst			*ft_get_string_token_node(char *str, size_t len,
									t_token_word_type word_type, int is_name);
t_string_compound_lst			*ft_get_word_element(char *str, char **s);
t_string_compound_lst			*ft_get_word_element_quote(char *str, char **s);
t_string_compound_lst			*ft_get_word_element_dquote(char *str,
									char **s);
t_string_compound_lst			*ft_get_escaped_character(char *str, char **s);
void							ft_remove_end_token(t_list **token_lst);

// Errors

void							ft_token_syntax_error(char *c);
void							ft_op_syntax_error(t_token_op_type op_code);
void							ft_token_missing_delimiter_error(char *c);
void							ft_token_missing_parenthesis(int op_code);

t_list							*ft_token_validity_checker(t_list *token_lst);
int								ft_is_redirection_valid(t_token_op_type *tktp,
									t_parsing_token *next_token);
int								ft_is_operator_valid(t_token_op_type *tktp,
									t_parsing_token *next_token,
									t_parsing_token *prev);

/// Utils

void							ft_print_token(t_list *token_lst, int depth);
void							ft_print_offset(int depth);
void							ft_print_tkn_op(t_parsing_token *parsing_token,
									int depth);
void							ft_print_tkn_w(t_parsing_token *parsing_token,
									int depth);
void							ft_print_lst(t_string_compound_lst *lst,
									int depth);

#endif
