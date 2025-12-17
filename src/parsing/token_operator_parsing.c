/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_parsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:29:55 by pberne            #+#    #+#             */
/*   Updated: 2025/12/17 18:42:35 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

// parenthesis
t_list	*ft_get_operator5(char *str, char **s)
{
	t_list	*ret;

	ret = 0;
	if (*str == '(')
	{
		str++;
		ret = ft_get_op_token(op_open_parenthesis);
	}
	else if (*str == ')')
	{
		str++;
		ret = ft_get_op_token(op_close_parenthesis);
	}
	*s = str;
	return (ret);
}

// out redirect
t_list	*ft_get_operator4(char *str, char **s)
{
	t_list	*ret;

	if (*str == '>')
	{
		str++;
		if (*str == '>')
		{
			str++;
			ret = ft_get_op_token(op_out_redirect_append);
		}
		else
			ret = ft_get_op_token(op_out_redirect_trunc);
	}
	else
		return (ft_get_operator5(str, s));
	*s = str;
	return (ret);
}

// in redirect, heredoc
t_list	*ft_get_operator3(char *str, char **s)
{
	t_list	*ret;

	if (*str == '<')
	{
		str++;
		if (*str == '<')
		{
			str++;
			ret = ft_get_op_token(op_heredoc);
		}
		else
			ret = ft_get_op_token(op_in_redirect);
	}
	else
		return (ft_get_operator4(str, s));
	*s = str;
	return (ret);
}

// and operator
t_list	*ft_get_operator2(char *str, char **s)
{
	t_list	*ret;

	if (*str == '&')
	{
		str++;
		if (*str == '&')
			ret = ft_get_op_token(op_and);
		else
		{
			ret = 0;
			ft_token_syntax_error("&");
		}
	}
	else
		return (ft_get_operator3(str, s));
	*s = str;
	return (ret);
}

/// @brief Extract an operator token and advances s to be on the
/// starting position of the next token
/// @return t_list * containing the constructed token as content,
///	or 0 on syntax error
t_list	*ft_get_operator(char *str, char **s)
{
	t_list	*ret;

	if (*str == '|')
	{
		str++;
		if (*str == '|')
		{
			str++;
			ret = ft_get_op_token(op_or);
		}
		else
			ret = ft_get_op_token(op_pipe);
	}
	else
		return (ft_get_operator2(str, s));
	*s = str;
	return (ret);
}
