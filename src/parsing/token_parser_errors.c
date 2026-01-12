/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:50:46 by pberne            #+#    #+#             */
/*   Updated: 2026/01/05 18:21:12 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"

void	ft_token_syntax_error(char *c)
{
	char	*str;

	str = ft_strjoin_mult_gc_id(malloc_id_token, 4, ft_get_progname(),
			": syntax error near unexpected token `", c, "\'\n");
	ft_putstr_fd(str, 2);
	ft_free(str);
}

void	ft_token_missing_delimiter_error(char *c)
{
	char	*str;

	str = ft_strjoin_mult_gc_id(malloc_id_token, 4, ft_get_progname(),
			": Missing closing delimiter `", c, "\'\n");
	ft_putstr_fd(str, 2);
	ft_free(str);
}

void	ft_token_missing_parenthesis(int op_code)
{
	char	*str;

	str = 0;
	if (op_code == op_open_parenthesis)
		str = ft_strjoin_gc_id(ft_get_progname(),
				": Missing matching parenthesis for `(\'\n", malloc_id_token);
	else if (op_code == op_close_parenthesis)
		str = ft_strjoin_gc_id(ft_get_progname(),
				": Missing matching parenthesis for `)\'\n", malloc_id_token);
	if (str)
		ft_putstr_fd(str, 2);
}

void	ft_op_syntax_error(t_token_op_type op_code)
{
	if (op_code == op_pipe)
		ft_token_syntax_error("|");
	else if (op_code == op_in_redirect)
		ft_token_syntax_error("<");
	else if (op_code == op_heredoc)
		ft_token_syntax_error("<<");
	else if (op_code == op_out_redirect_trunc)
		ft_token_syntax_error(">");
	else if (op_code == op_out_redirect_append)
		ft_token_syntax_error(">>");
	else if (op_code == op_open_parenthesis)
		ft_token_syntax_error("(");
	else if (op_code == op_close_parenthesis)
		ft_token_syntax_error(")");
	else if (op_code == op_and)
		ft_token_syntax_error("&&");
	else if (op_code == op_or)
		ft_token_syntax_error("||");
}
