/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:07:40 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 11:39:48 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

char	*ft_expand_word_var(char **word, char *dest, t_shell_data *data)
{
	char	*varname;

	varname = ft_getvarname(*word + 1);
	*word += ft_strlen(varname) + 1;
	dest = ft_strjoin_gc_id(dest, ft_getvar(data->vars, data->envp, data->argv,
				varname), malloc_id_exec);
	return (dest);
}

int	ft_try_skip_orphan_dollar(char **word, char **dest,
		t_string_compound_lst *cmpd_node)
{
	if (!(*word)[1] || (!ft_isalnum((*word)[1]) && (*word)[1] != '?'))
	{
		if ((*word)[1] || !cmpd_node->is_naked || !cmpd_node->next)
			*dest = ft_strjoin_gc_id(*dest, "$", malloc_id_exec);
		*word += 1;
		return (1);
	}
	return (0);
}

char	*ft_expand_word(char *word, t_shell_data *data,
		t_string_compound_lst *cmpd_node)
{
	char	*dest;

	dest = NULL;
	if (!word)
		return (NULL);
	while (*word)
	{
		if (*word == '$')
		{
			if (ft_try_skip_orphan_dollar(&word, &dest, cmpd_node))
				continue ;
			if (cmpd_node)
				cmpd_node->is_expanded = 1;
			dest = ft_expand_word_var(&word, dest, data);
		}
		else
			dest = ft_copy_nonspecial(&word, dest);
	}
	if (dest == NULL)
		dest = ft_strdup_gc_id("", malloc_id_exec);
	return (dest);
}

/// @brief Iterates through the compound list and substitutes ~ with
/// the value of the HOME variable
void	ft_expand_tilde(t_string_compound_lst *cmpd, char *home_path)
{
	if (cmpd->type == word_replace_vars)
	{
		if (ft_strhasc(cmpd->str, '~') && cmpd->str[0] == '~' && !cmpd->next
			&& cmpd->is_naked)
		{
			if (ft_strhasc(cmpd->str, '/'))
				cmpd->str = ft_strjoin_gc_id(home_path, cmpd->str + 1,
						malloc_id_exec);
			else
				cmpd->str = home_path;
		}
	}
}

/// @brief Iterates through the compound list and substitutes str
/// with a str including the variable expansion
void	ft_expand_compound(t_string_compound_lst *cmpd, t_shell_data *data)
{
	while (cmpd)
	{
		if (cmpd->type == word_replace_vars && ft_strcmp("", cmpd->str))
			cmpd->str = ft_expand_word(cmpd->str, data, cmpd);
		cmpd = cmpd->next;
	}
}
