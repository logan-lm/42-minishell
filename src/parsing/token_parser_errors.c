/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:50:46 by pberne            #+#    #+#             */
/*   Updated: 2025/12/18 12:02:07 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

void	ft_token_syntax_error(char *c)
{
	char	*str;

	str = ft_strjoin_mult_gc(3, "syntax error near unexpected token `", c,
			"\'\n");
	ft_putstr_fd(str, 2);
	ft_free(str);
}

void	ft_token_missing_delimiter_error(char *c)
{
	char	*str;

	str = ft_strjoin_mult_gc(3, "Missing closing delimiter `", c, "\'\n");
	ft_putstr_fd(str, 2);
	ft_free(str);
}

void	ft_token_missing_parenthesis(int op_code)
{
	if (op_code == op_open_parenthesis)
		ft_putstr_fd("Missing matching parenthesis for `(\'\n", 2);
	else if (op_code == op_close_parenthesis)
		ft_putstr_fd("Missing matching parenthesis for `)\'\n", 2);
}
