/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:07:40 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 12:04:09 by lomartin         ###   ########.fr       */
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
		if (!ft_isdir(temp) && !access(temp, F_OK))
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

int	ft_check_cmdaccess(char *path, char *progname, int *ret)
{
	char	*err;

	if (ft_isdir(path))
	{
		err = ft_strjoin_gc_id(path, ": Is a directory", malloc_id_exec);
		*ret = 126;
		ft_print_error(err, progname);
		ft_free(err);
		return (0);
	}
	if (access(path, F_OK))
	{
		*ret = 127;
		ft_print_perror(path, progname);
		return (0);
	}
	if (access(path, R_OK | W_OK))
	{
		*ret = 126;
		ft_print_perror(path, progname);
		return (0);
	}
	return (1);
}

char	*ft_get_cmdpath(char *cmd, t_list *envp, int *ret, char *progname)
{
	char	*path;

	if (ft_ispath(cmd))
	{
		if (ft_check_cmdaccess(cmd, progname, ret))
			return (ft_parse_path(cmd, envp));
		else
			return (NULL);
	}
	path = ft_check_paths(cmd, envp);
	if (path)
		return (path);
	ft_free(path);
	if (errno == 13)
	{
		ft_print_perror(cmd, progname);
		*ret = 126;
	}
	else
	{
		ft_print_error(ft_strjoin_gc_id(cmd, ": command not found",
				malloc_id_exec), progname);
		*ret = 127;
	}
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
			dest = ft_strjoin_gc_id(dest, ft_getvar(data->vars, data->envp, data->argv,
						varname), malloc_id_exec);
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
