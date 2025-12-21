/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:07:46 by pberne            #+#    #+#             */
/*   Updated: 2025/12/21 15:33:16 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

t_list	*ft_get_op_token(t_token_op_type op_type)
{
	t_parsing_token	*token;
	t_token_op_type	*new_op_type;

	token = ft_malloc(sizeof(t_parsing_token));
	new_op_type = ft_malloc(sizeof(t_token_op_type));
	token->type = token_op;
	*new_op_type = op_type;
	token->data = new_op_type;
	return (ft_lstnew_gc(token));
}

t_list	*ft_get_end_token(void)
{
	t_parsing_token	*token;

	token = ft_malloc(sizeof(t_parsing_token));
	token->type = token_end;
	return (ft_lstnew_gc(token));
}

t_list	*ft_get_token(char **s)
{
	char	*str;
	t_list	*ret;

	str = *s;
	while (*str && ft_strchr(" \t", *str))
		str++;
	*s = str;
	if (*str == '\0')
		ret = ft_get_end_token();
	else if (ft_strchr("|&()<>=", *str))
		ret = ft_get_operator(str, s);
	else
		ret = ft_get_word(str, s);
	return (ret);
}

t_list	*ft_get_tokens(char *str)
{
	t_list	*lst;
	t_list	*new_token;

	lst = 0;
	while (1)
	{
		new_token = ft_get_token(&str);
		if (new_token)
		{
			ft_lstadd_back(&lst, new_token);
			if (((t_parsing_token *)new_token->content)->type == token_end)
				break ;
		}
		else
		{
			ft_free_token_list(lst);
			break ;
		}
	}
	return (ft_token_validity_checker(lst));
}
