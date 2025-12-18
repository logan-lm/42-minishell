/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operator_parsing_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:29:55 by pberne            #+#    #+#             */
/*   Updated: 2025/12/18 15:02:30 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

// equal
t_list	*ft_get_operator6(char *str, char **s)
{
	t_list	*ret;

	ret = 0;
	if (*str == '=')
	{
		str++;
		ret = ft_get_op_token(op_equal);
	}
	*s = str;
	return (ret);
}
