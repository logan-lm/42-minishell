/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_literal_parsing_compound.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:29:41 by pberne            #+#    #+#             */
/*   Updated: 2025/12/18 15:04:33 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

t_string_compound_lst	*ft_get_literal_element(char *str, char **s)
{
	size_t					i;
	t_string_compound_lst	*ret;

	i = 0;
	while (str[i] && ft_strchr("|&()<>= '\"\t", str[i]) == 0)
		i++;
	ret = ft_get_string_token_node(str, i, literal_replace_vars);
	*s = str + i;
	return (ret);
}

t_string_compound_lst	*ft_get_literal_element_quote(char *str, char **s)
{
	t_string_compound_lst	*ret;
	int						i;

	i = 0;
	str++;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] != '\'')
	{
		ft_token_missing_delimiter_error("\'");
		return (0);
	}
	ret = ft_get_string_token_node(str, i, literal_true);
	*s = str + i + 1;
	return (ret);
}

t_string_compound_lst	*ft_get_literal_element_dquote(char *str, char **s)
{
	t_string_compound_lst	*ret;
	int						i;

	i = 0;
	str++;
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] != '"')
	{
		ft_token_missing_delimiter_error("\"");
		return (0);
	}
	ret = ft_get_string_token_node(str, i, literal_replace_vars);
	*s = str + i + 1;
	return (ret);
}
