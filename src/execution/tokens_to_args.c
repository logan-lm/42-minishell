/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 21:37:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/12 22:15:40 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

t_list	*ft_wordtolst(t_string_compound_lst *word)
{
	t_list	*args;

	args = NULL;
	while (word)
	{
		x
		word = word->next;
	}
}

char	**ft_tokens_to_args(t_list *nodes)
{
	t_parsing_token			*tokens;
	t_list					**args;

	args = NULL;
	tokens = nodes->content;
	while (tokens)
	{
		if (tokens->type == token_op
			&& ((t_token_op_data *)(tokens->data))->type == op_pipe)
			return (ft_lsttostrs(args));
		if (tokens->type == token_subshell)
			ft_lstmerge(ft_subshelltolst());
		if (tokens->type == token_word)
			ft_lstmerge(ft_wordstolst(tokens->data));
		nodes = nodes->next;
		tokens = nodes->content;
	}
	return (ft_lsttostrs(args));
}

