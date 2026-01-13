/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:07:40 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/13 20:31:04 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	*ft_get_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3))
		return (ft_cd);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd);
	if (!ft_strncmp(cmd, "env", 4))
		return (ft_env);
	if (!ft_strncmp(cmd, "echo", 5))
		return (ft_echo);
	if (!ft_strncmp(cmd, "unset", 6))
		return (ft_unset);
	if (!ft_strncmp(cmd, "export", 7))
		return (ft_export);
	if (!ft_strncmp(cmd, "exit", 6))
		return (ft_shell_exit);
	if (!ft_strncmp(cmd, "()", 3))
		return (ft_subshell);
	if (ft_is_varset(cmd))
		return (ft_set_var);
	return (NULL);
}

int	ft_is_only_varset(t_list *commands)
{
	t_command	*cmd;

	while (commands)
	{
		cmd = commands->content;
		if (!ft_is_varset(*(cmd->args)))
			return (0);
		commands = commands->next;
	}
	return (1);
}

char	*ft_expand_word_var(char **word, char *dest, t_shell_data *data)
{
	char	*varname;

	varname = ft_getvarname(*word + 1);
	*word += ft_strlen(varname) + 1;
	dest = ft_strjoin_gc_id(dest, ft_getvar(data->vars, data->envp, data->argv,
				varname), malloc_id_exec);
	return (dest);
}

char	*ft_expand_word(char *word, t_shell_data *data,
		t_string_compound_lst *cmpd_node)
{
	char	*dest;
	char	*temp;

	dest = NULL;
	if (!word)
		return (NULL);
	while (*word)
	{
		temp = dest;
		if (*word == '$')
		{
			if (!word[1] || (!ft_isalnum(word[1]) && word[1] != '?'))
			{
				if (word[1] || !cmpd_node->is_naked || !cmpd_node->next)
					dest = ft_strjoin_gc_id(dest, "$", malloc_id_exec);
				word++;
				continue ;
			}
			if (cmpd_node)
				cmpd_node->is_expanded = 1;
			dest = ft_expand_word_var(&word, dest, data);
		}
		else
			dest = ft_copy_nonspecial(&word, dest);
		ft_free(temp);
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
		if (ft_strhasc(cmpd->str, '~') && cmpd->str[0] == '~')
		{
			cmpd->str = ft_strjoin_gc_id(home_path, cmpd->str + 1,
					malloc_id_exec);
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
