/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/22 20:53:01 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "command.h"

void	ft_test_cmds(t_list **cmds)
{
	//SUBSHELL
	t_token_op_data *subshell_token_in;
	subshell_token_in = ft_malloc(sizeof(t_token_op_data));
	subshell_token_in->type = op_in_redirect;
	t_string_compound_lst *subshell_list_in;
	subshell_list_in = ft_malloc(sizeof(t_string_compound_lst));
	subshell_list_in->next = NULL;
	subshell_list_in->str = "infile";
	subshell_list_in->type = word_replace_vars;
	subshell_token_in->word = subshell_list_in;
	t_token_op_data *subshell_token_out;
	subshell_token_out = ft_malloc(sizeof(t_token_op_data));
	subshell_token_out->type = op_out_redirect_trunc;
	t_string_compound_lst *subshell_list_out;
	subshell_list_out = ft_malloc(sizeof(t_string_compound_lst));
	subshell_list_out->next = NULL;
	subshell_list_out->str = "infile";
	subshell_list_out->type = word_replace_vars;
	subshell_token_out->word = subshell_list_out;
	t_command_node	*subshell;
	subshell = ft_malloc(sizeof(t_command_node));
	subshell->type = command_subshell;
	subshell->right = NULL;
	ft_lstadd_back(&subshell->pipeline, ft_lstnew(subshell_token_in));
	ft_lstadd_back(&subshell->pipeline, ft_lstnew(subshell_token_out));

	//AND
	t_command_node *and;
	and = ft_malloc(sizeof(t_command_node));
	and->type = command_and;
	and->pipeline = NULL;

	//CAT1
	t_token_op_data *cat1_token;
	cat1_token = ft_malloc(sizeof(t_token_op_data));
	cat1_token->type = op_pipe;
	t_string_compound_lst *cat1_list;
	cat1_list = ft_malloc(sizeof(t_string_compound_lst));
	cat1_list->next = NULL;
	cat1_list->str = "cat";
	cat1_list->type = word_replace_vars;
	cat1_token->word = cat1_list;
	t_command_node *cat1;
	cat1 = ft_malloc(sizeof(t_command_node));
	cat1->type = command_pipeline;
	cat1->left = NULL;
	cat1->right = NULL;
	ft_lstadd_back(&cat1->pipeline, ft_lstnew(cat1_token));
	and->left = cat1;

	//CAT2
	t_token_op_data *cat2_token;
	cat2_token = ft_malloc(sizeof(t_token_op_data));
	cat2_token->type = op_pipe;
	t_string_compound_lst *cat2_list;
	cat2_list = ft_malloc(sizeof(t_string_compound_lst));
	cat2_list->next = NULL;
	cat2_list->str = "cat";
	cat2_list->type = word_replace_vars;
	cat2_token->word = cat2_list;
	t_token_op_data *cat2_token_redir;
	cat2_token = ft_malloc(sizeof(t_token_op_data));
	cat2_token->type = op_out_redirect_trunc;
	t_string_compound_lst *cat2_list_redir;
	cat2_list_redir = ft_malloc(sizeof(t_string_compound_lst));
	cat2_list_redir->next = NULL;
	cat2_list_redir->str = "testa";
	cat2_list_redir->type = word_replace_vars;
	cat2_token_redir->word = cat2_list_redir;
	t_command_node *cat2;
	cat2 = ft_malloc(sizeof(t_command_node));
	cat2->type = command_pipeline;
	cat2->left = NULL;
	cat2->right = NULL;
	ft_lstadd_back(&cat2->pipeline, ft_lstnew(cat2_token));
	ft_lstadd_back(&cat2->pipeline, ft_lstnew(cat2_token_redir));
	and->right = cat2;

	subshell->left = and;
	ft_lstadd_back(cmds, ft_lstnew(subshell));
}

void	ft_exec(t_list *cmds, t_shell_data *d)
{
	t_list			*top;
	t_command_node	*cmd;

	(void)d;
	ft_test_cmds(&cmds);
	top = cmds;
	while (*top)
	{
		cmd = top->content;
		if (cmd->type == command_pipeline)
		top = top->next;
	}
}
