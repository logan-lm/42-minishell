/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:07:40 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 10:20:51 by lomartin         ###   ########.fr       */
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

char	*ft_expand_word(char *word, t_shell_data *data)
{
	char	*dest;
	char	*varname;
	char	*temp;

	dest = NULL;
	if (!word)
		return (NULL);
	while (*word)
	{
		temp = dest;
		if (*word == '$')
		{
			if (!word[1] || !ft_isalnum(word[1]))
			{
				dest = ft_strjoin_gc_id(dest, "$", malloc_id_exec);
				word++;
				continue ;
			}
			varname = ft_getvarname(word + 1);
			word += ft_strlen(varname) + 1;
			dest = ft_strjoin_gc_id(dest, ft_getvar(data->vars, data->envp,
						data->argv, varname), malloc_id_exec);
		}
		else
			dest = ft_copy_nonspecial(&word, dest);
		ft_free(temp);
	}
	return (dest);
}

char	*ft_expand_compound(t_string_compound_lst *cmpd, t_shell_data *data)
{
	char	*dest;
	char	*temp;

	dest = NULL;
	while (cmpd)
	{
		temp = dest;
		if (cmpd->type == word_replace_vars)
		{
			dest = ft_strjoin_gc_id(dest, ft_expand_word(cmpd->str, data),
					malloc_id_exec);
		}
		else
			dest = ft_strjoin_gc_id(dest, cmpd->str, malloc_id_exec);
		ft_free(temp);
		cmpd = cmpd->next;
	}
	return (dest);
}
