/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 09:52:58 by pberne            #+#    #+#             */
/*   Updated: 2025/12/29 14:17:24 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_name_character(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	ft_is_assignement_op(char *str, int *i)
{
	if (str[*i] == '=')
	{
		*i += 1;
		return (1);
	}
	else if (str[*i] == '+' && str[*i + 1] == '=')
	{
		*i += 2;
		return (1);
	}
	return (0);
}

t_string_compound_lst	*ft_build_word_token(char *str)
{
	t_string_compound_lst	*ret;
	int						i;
	int						j;

	i = 0;
	while (str[i] && ft_is_name_character(str[i]))
		i++;
	if (i > 0 && ft_isalpha(str[0]) && ft_is_assignement_op(str, &i))
	{
		ret = ft_get_string_token_node(str, i, word_true, (t_v2i){1, 1});
		j = i;
		while (str[j])
			j++;
		if (i != j)
			ret->next = ft_get_string_token_node(str + i, j - i,
					word_replace_vars, (t_v2i){0, 1});
	}
	else
	{
		while (str[i])
			i++;
		ret = ft_get_string_token_node(str, i, word_replace_vars, (t_v2i){0,
				1});
	}
	return (ret);
}
