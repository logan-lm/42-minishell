/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 09:52:58 by pberne            #+#    #+#             */
/*   Updated: 2025/12/27 09:52:59 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_name_character(char c)
{
	return (ft_isalnum(c) || c == '_');
}

t_string_compound_lst	*ft_build_word_token(char *str)
{
	t_string_compound_lst	*ret;
	int						i;
	int						j;

	i = 0;
	while (str[i] && ft_is_name_character(str[i]))
		i++;
	if (i > 0 && str[i] == '=' && ft_isalpha(str[0]))
	{
		i++;
		ret = ft_get_string_token_node(str, i, word_true, 1);
		j = i;
		while (str[j])
			j++;
		if (i != j)
			ret->next = ft_get_string_token_node(str + i, j - i,
					word_replace_vars, 0);
	}
	else
	{
		while (str[i])
			i++;
		ret = ft_get_string_token_node(str, i, word_replace_vars, 0);
	}
	return (ret);
}
