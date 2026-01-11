/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:38:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 21:30:20 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_parse_cmd_while(t_parsecmd_data *p_d, t_shell_data *d)
{
	p_d->token = p_d->nodes_cpy->content;
	p_d->op_token = p_d->token->data;
	if (p_d->token->type == token_op)
	{
		if (p_d->op_token->type == op_pipe)
			return (1);
	}
	if (p_d->token->type == token_subshell)
	{
		ft_lstadd_back(&p_d->args_lst, ft_lstnew_gc_id("()", malloc_id_exec));
		ft_lstadd_back(&p_d->args_lst, ft_lstnew_gc_id(p_d->token->data,
				malloc_id_exec));
	}
	if (p_d->token->type == token_word)
		p_d->args_lst = ft_lstmerge(p_d->args_lst,
				ft_parse_cmd_args(p_d->token->data, d));
	p_d->nodes_cpy = p_d->nodes_cpy->next;
	return (0);
}

t_list	*ft_parse_cmd(t_list **nodes, t_shell_data *d)
{
	t_parsecmd_data	p_d;

	p_d.args_lst = NULL;
	p_d.nodes_cpy = *nodes;
	while (p_d.nodes_cpy)
	{
		if (ft_parse_cmd_while(&p_d, d) == 1)
			break ;
	}
	return (p_d.args_lst);
}

t_list	*ft_parse_args_replace(t_string_compound_lst *tokens, t_list **src,
		t_shell_data *data)
{
	if (!*src)
		ft_lstadd_back(src, ft_lstnew_gc_id(ft_strdup_gc_id("", malloc_id_exec),
				malloc_id_exec));
	ft_wordtostr(tokens->str, src, data, tokens->next);
	if (tokens->is_naked)
		(*src) = ft_check_wildcards(*src, data);
	return (*src);
}

t_list	*ft_parse_args_append(t_string_compound_lst *tokens, t_list **src)
{
	char	*temp;
	t_list	*cpy;

	cpy = *src;
	if (!cpy)
		ft_lstadd_back(src, ft_lstnew_gc_id(tokens->str, malloc_id_exec));
	else
	{
		while (cpy)
		{
			temp = (cpy)->content;
			(cpy)->content = ft_strjoin_gc_id((cpy)->content, tokens->str,
					malloc_id_exec);
			ft_free(temp);
			cpy = cpy->next;
		}
	}
	return (*src);
}

t_list	*ft_parse_cmd_args(t_string_compound_lst *tokens, t_shell_data *data)
{
	t_list	*args;
	char	*temp;

	args = NULL;
	data->wc_path = NULL;
	while (tokens)
	{
		if (tokens->type == word_replace_vars)
			args = ft_parse_args_replace(tokens, &args, data);
		else if (tokens->type == word_true)
		{
			if (data->wc_path)
			{
				temp = data->wc_path;
				data->wc_path = ft_strjoin_gc_id(data->wc_path, tokens->str,
						malloc_id_exec);
				ft_free(temp);
			}
			else
				args = ft_parse_args_append(tokens, &args);
		}
		tokens = tokens->next;
	}
	args = ft_get_matching_names(args, data->wc_path);
	return (args);
}
