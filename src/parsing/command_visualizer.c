/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_visualizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 16:28:59 by pberne            #+#    #+#             */
/*   Updated: 2025/12/24 17:14:15 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

#include "minishell.h"
#include "parser.h"

static void	ft_prepare_prefix(char *old_prefix, char *new_prefix, int is_last)
{
	ft_strlcpy(new_prefix, old_prefix, 1024);
	if (is_last)
		ft_strlcat(new_prefix, "    ", 1024);
	else
		ft_strlcat(new_prefix, "│   ", 1024);
}

void	ft_print_word_content(t_string_compound_lst *lst, char *prefix)
{
	while (lst)
	{
		ft_printf("%s%s", prefix, lst->next == NULL ? "└╴ " : "├╴ ");
		ft_printf("(%d): %s\n", lst->type, lst->str);
		lst = lst->next;
	}
}

void	ft_print_pipeline_contents(t_list *token_lst, char *prefix)
{
	t_parsing_token	*token;
	char			next_prefix[1024];
	int				is_last;

	while (token_lst)
	{
		token = (t_parsing_token *)token_lst->content;
		is_last = (token_lst->next == NULL);

		ft_printf("%s%s", prefix, is_last ? "└╴ " : "├╴ ");
		ft_prepare_prefix(prefix, next_prefix, is_last);

		if (token->type == token_word)
		{
			ft_printf("[WORD]\n");
			ft_print_word_content(
				(t_string_compound_lst *)token->data,
				next_prefix
			);
		}
		else if (token->type == token_op)
		{
			t_token_op_data *op = (t_token_op_data *)token->data;

			ft_printf("[OP: %d]\n", op->type);
			if (op->word)
				ft_print_word_content(op->word, next_prefix);
		}
		else if (token->type == token_subshell)
		{
			ft_printf("[SUBSHELL]\n");
			ft_print_ast_visual(
				(t_command_node *)token->data,
				next_prefix
			);
		}
		token_lst = token_lst->next;
	}
}

void	ft_print_ast_visual(t_command_node *node, char *prefix)
{
	char	next_prefix[1024];

	if (!node)
		return ;

	if (node->type == command_and || node->type == command_or)
	{
		ft_printf(
			"%s%s\n",
			prefix,
			node->type == command_and ? "AND" : "OR"
		);
		ft_printf("%s├╴ Left:\n", prefix);
		ft_prepare_prefix(prefix, next_prefix, 0);
		ft_print_ast_visual(node->left, next_prefix);
		ft_printf("%s└╴ Right:\n", prefix);
		ft_prepare_prefix(prefix, next_prefix, 1);
		ft_print_ast_visual(node->right, next_prefix);
	}
	else if (node->type == command_pipeline)
	{
		ft_printf("%sPIPELINE\n", prefix);
		ft_prepare_prefix(prefix, next_prefix, 1);
		ft_print_pipeline_contents(node->commands, next_prefix);
	}
}
