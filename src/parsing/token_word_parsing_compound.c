/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_parsing_compound.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:29:41 by pberne            #+#    #+#             */
/*   Updated: 2026/01/05 17:24:44 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

t_string_compound_lst	*ft_get_word_element(char *str, char **s)
{
	size_t					i;
	t_string_compound_lst	*ret;
	char					*word_substr;

	i = 0;
	while (str[i] && ft_strchr("|&()<> '\"\t", str[i]) == 0)
		i++;
	word_substr = ft_substr_gc_id(str, 0, i, malloc_id_token);
	ret = ft_build_word_token(word_substr);
	*s = str + i;
	return (ret);
}

t_string_compound_lst	*ft_get_word_element_quote(char *str, char **s)
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
	ret = ft_get_string_token_node(str, i, word_true, (t_v2i){0, 0});
	*s = str + i + 1;
	return (ret);
}

t_string_compound_lst	*ft_get_word_element_dquote(char *str, char **s)
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
	ret = ft_get_string_token_node(str, i, word_replace_vars, (t_v2i){0, 0});
	*s = str + i + 1;
	return (ret);
}

t_string_compound_lst	*ft_get_escaped_character(char *str, char **s)
{
	t_string_compound_lst	*new_compound;

	new_compound = ft_malloc_id(sizeof(t_string_compound_lst), malloc_id_token);
	new_compound->type = word_true;
	new_compound->next = 0;
	str = *s;
	if (str[1] == '\0')
	{
		new_compound->str = ft_substr_gc_id(str, 0, 1, malloc_id_token);
		*s += 1;
	}
	else
	{
		new_compound->str = ft_substr_gc_id(str, 1, 1, malloc_id_token);
		*s += 2;
	}
	new_compound->is_naked = 1;
	return (new_compound);
}
