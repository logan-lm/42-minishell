/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:38:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 13:42:08 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	ft_parse_cmd_while(t_parsecmd_data *p_d, t_shell_data *d)
{
	while (p_d->nodes_cpy)
	{
		p_d->token = p_d->nodes_cpy->content;
		p_d->op_token = p_d->token->data;
		if (p_d->token->type == token_op)
		{
			if (p_d->op_token->type == op_pipe)
				break ;
		}
		if (p_d->token->type == token_subshell)
		{
			ft_lstadd_back(&p_d->args_lst, ft_lstnew_gc("()"));
			ft_lstadd_back(&p_d->args_lst, ft_lstnew_gc(p_d->token->data));
		}
		if (p_d->token->type == token_word)
			p_d->args_lst = ft_lstmerge(p_d->args_lst,
					ft_parse_cmd_args(p_d->token->data, d));
		if ((p_d->args_lst && ft_is_varset(ft_lstlast(p_d->args_lst)->content)))
		{
			p_d->token->type = token_op;
			p_d->op_token->type = op_pipe;
			break ;
		}
		p_d->nodes_cpy = p_d->nodes_cpy->next;
	}
}

t_list	*ft_parse_cmd(t_list **nodes, t_shell_data *d)
{
	t_parsecmd_data	p_d;

	p_d.args_lst = NULL;
	p_d.nodes_cpy = *nodes;
	ft_parse_cmd_while(&p_d, d);
	return (p_d.args_lst);
}

t_list	*ft_parse_args_replace(t_string_compound_lst *tokens, t_list **src,
		t_shell_data *data)
{
	if (!*src)
		ft_lstadd_back(src, ft_lstnew_gc(ft_strdup_gc("")));
	ft_wordtostr(tokens->str, src, data);
	(*src) = ft_check_wildcards(*src, data);
	return (*src);
}

t_list	*ft_parse_args_append(t_string_compound_lst *tokens, t_list **src)
{
	char	*temp;
	t_list	*cpy;

	cpy = *src;
	if (!cpy)
		ft_lstadd_back(src, ft_lstnew_gc(tokens->str));
	else
	{
		while (cpy)
		{
			temp = (cpy)->content;
			(cpy)->content = ft_strjoin_gc((cpy)->content, tokens->str);
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
				data->wc_path = ft_strjoin_gc(data->wc_path, tokens->str);
				free(temp);
			}
			else
				args = ft_parse_args_append(tokens, &args);
		}
		tokens = tokens->next;
	}
	args = ft_get_matching_names(args, data->wc_path);
	return (args);
}
