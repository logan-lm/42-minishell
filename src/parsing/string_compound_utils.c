/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_compound_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:17:19 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 07:33:15 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

t_string_compound_lst	*ft_copy_str_cmpd_flags(t_string_compound_lst *src)
{
	t_string_compound_lst	*dest;

	dest = ft_malloc_id(sizeof(t_string_compound_lst), malloc_id_exec);
	dest->is_naked = src->is_naked;
	dest->is_expanded = src->is_expanded;
	dest->type = src->type;
	dest->str = NULL;
	return (dest);
}

char	*ft_str_cmpd_to_str(t_string_compound_lst *cmpd_lst)
{
	char					*dest;
	size_t					len;
	t_string_compound_lst	*iterator;

	dest = 0;
	len = 0;
	iterator = cmpd_lst;
	while (iterator)
	{
		len += ft_strlen(iterator->str);
		iterator = iterator->next;
	}
	dest = ft_malloc_id(len + 1, malloc_id_exec);
	dest[len] = '\0';
	len = 0;
	iterator = cmpd_lst;
	while (iterator)
	{
		len += ft_strlcpy(dest + len, iterator->str, ft_strlen(iterator->str)
				+ 1);
		iterator = iterator->next;
	}
	return (dest);
}

void	ft_str_consume_spaces(t_string_compound_lst *cmpd)
{
	char	*str;

	str = cmpd->str;
	while (*str && ft_isspace(*str))
		str++;
	cmpd->str = str;
}

char	*ft_expand_compound_for_var(t_string_compound_lst *cmpd,
		t_shell_data *data)
{
	char	*dest;
	char	*temp;

	dest = NULL;
	while (cmpd)
	{
		temp = dest;
		if (cmpd->type == word_replace_vars)
		{
			dest = ft_strjoin_gc_id(dest, ft_expand_word(cmpd->str, data, 0),
					malloc_id_exec);
		}
		else
			dest = ft_strjoin_gc_id(dest, cmpd->str, malloc_id_exec);
		ft_free(temp);
		cmpd = cmpd->next;
	}
	return (dest);
}
