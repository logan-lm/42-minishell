/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:13:32 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 17:30:53 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_pipe(t_list *nodes)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;

	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
				return (1);
		}
		nodes = nodes->next;
	}
	return (0);
}

t_list	*ft_next_cmd(t_list *nodes)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;

	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
			if (op_token->type == op_pipe)
				return (nodes->next);
		}
		nodes = nodes->next;
	}
	return (NULL);
}

t_list	*ft_separate_cmdname(char *arg)
{
	char	*temp;
	int		i;
	int		j;
	t_list	*args;

	temp = ft_calloc_gc_id(ft_strclen(arg, ' '), sizeof(char), malloc_id_exec);
	i = 0;
	j = 0;
	args = NULL;
	while (arg[j] != ' ')
		temp[i++] = arg[j++];
	temp[i] = '\0';
	ft_lstadd_front(&args, ft_lstnew_gc_id(temp, malloc_id_exec));
	while (arg[j] == ' ')
		j++;
	temp = ft_calloc_gc_id(ft_strlen(temp + j), sizeof(char), malloc_id_exec);
	i = 0;
	while (arg[j])
		temp[i++] = arg[j++];
	temp[i] = '\0';
	ft_lstadd_back(&args, ft_lstnew_gc_id(temp, malloc_id_exec));
	return (args);
}
