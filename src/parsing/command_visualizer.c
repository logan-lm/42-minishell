/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_visualizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 16:28:59 by pberne            #+#    #+#             */
/*   Updated: 2025/12/25 23:07:47 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void		ft_print_word_content(t_string_compound_lst *lst, char *prefix);
void		ft_print_op_content(char *next_prefix, t_parsing_token *token);

static void	ft_prepare_prefix(char *old_prefix, char *new_prefix, int is_last)
{
	ft_strlcpy(new_prefix, old_prefix, 1024);
	if (is_last)
		ft_strlcat(new_prefix, "    ", 1024);
	else
		ft_strlcat(new_prefix, "│   ", 1024);
}

void	ft_print_pipeline_contents(t_list *token_lst, char *prefix,
		t_parsing_token *token)
{
	char	next_prefix[1024];

	while (token_lst)
	{
		token = (t_parsing_token *)token_lst->content;
		if (token_lst->next == NULL)
			ft_printf("%s%s", prefix, "└╴ ");
		else
			ft_printf("%s%s", prefix, "├╴ ");
		ft_prepare_prefix(prefix, next_prefix, token_lst->next == NULL);
		if (token->type == token_word)
		{
			ft_printf("[WORD]\n");
			ft_print_word_content((t_string_compound_lst *)token->data,
				next_prefix);
		}
		else if (token->type == token_op)
			ft_print_op_content(next_prefix, token);
		else if (token->type == token_subshell)
		{
			ft_printf("[SUBSHELL]\n");
			ft_print_ast_visual((t_command_node *)token->data, next_prefix);
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
		if (node->type == command_and)
			ft_printf("%s%s\n", prefix, "AND");
		else
			ft_printf("%s%s\n", prefix, "OR");
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
		ft_print_pipeline_contents(node->commands, next_prefix, 0);
	}
}
