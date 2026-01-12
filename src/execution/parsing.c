/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:38:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/12 17:50:34 by lomartin         ###   ########.fr       */
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
	ft_wordtostr(tokens->str, src, data, tokens->next && tokens->is_naked);
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

t_list	*ft_parse_cmd_args(t_string_compound_lst *t, t_shell_data *d)
{
	t_parse_cmd_args_data	ca_d;

	ft_bzero(&ca_d, sizeof(ca_d));
	while (t)
	{
		if (t->type == word_replace_vars)
			ca_d.args = ft_parse_args_replace(t, &ca_d.args, d);
		else if (t->type == word_true)
		{
			ca_d.l = ft_lstlast(ca_d.args);
			if (d->wc_path)
			{
				ca_d.temp = d->wc_path;
				d->wc_path = ft_strjoin_gc_id(d->wc_path, t->str, 3);
				ft_free(ca_d.temp);
			}
			else if (ca_d.l)
				ca_d.l->content = ft_strjoin_gc_id(ca_d.l->content, t->str, 3);
			else
				ft_lstadd_front(&ca_d.args, ft_lstnew_gc_id(t->str, 3));
		}
		t = t->next;
	}
	return (ft_chech_matchs(ca_d.args, d));
}
