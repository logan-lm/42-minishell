/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:07:40 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/07 22:14:58 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

char	*ft_check_paths(char *cmdname, t_list *envp)
{
	char	*temp;
	char	**paths;
	int		i;

	temp = ft_dictmap(envp, "PATH");
	if (!temp)
		return (NULL);
	paths = ft_split_gc_id(temp, ':', malloc_id_exec);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_mult_gc_id(malloc_id_exec, 3, paths[i], "/", cmdname);
		if (!access(temp, F_OK))
		{
			ft_free_strs(paths);
			return (temp);
		}
		ft_free(temp);
		i++;
	}
	ft_free_strs(paths);
	return (NULL);
}

char	*ft_get_cmdpath(char *cmd, t_list *envp, int *ret)
{
	char	*path;
	char	*err;

	if (ft_ispath(cmd))
		return (ft_parse_path(cmd, envp));
	path = ft_check_paths(cmd, envp);
	if (path)
		return (path);
	err = ft_strjoin_gc_id(cmd, ": command not found \n", malloc_id_exec);
	if (errno == 13)
		*ret = 126;
	*ret = 127;
	ft_putstr_fd(err, 2);
	ft_free(err);
	return (NULL);
}

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
			dest = ft_strjoin_gc_id(dest, ft_getvar(data->vars, data->envp, varname), malloc_id_exec);
		}
		else
			dest = ft_copy_nonspecial(&word, dest);
		ft_free(temp);
	}
	return (dest);
}
