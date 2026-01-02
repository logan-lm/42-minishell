/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 14:38:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/02 16:11:19 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

t_list	*ft_parse_cmd(t_list **nodes, t_shell_data *d)
 {
	t_parsing_token	*token;
	t_token_op_data	*op_token;
	t_list			*args_lst;
	t_list			*nodes_cpy;

    args_lst = NULL;
	nodes_cpy = *nodes;
  	while (nodes_cpy)
	{
		token = nodes_cpy->content;
		op_token = token->data;
		if (token->type == token_op)
		{
			if (op_token->type == op_pipe)
				break ;
		}
		if (token->type == token_subshell)
		{
			ft_lstadd_back(&args_lst, ft_lstnew_gc("()"));
			ft_lstadd_back(&args_lst, ft_lstnew_gc(token->data));
		}
		if (token->type == token_word)
			args_lst = ft_lstmerge(args_lst, ft_parse_cmd_args(token->data, d));
		if ((args_lst && ft_is_varset(ft_lstlast(args_lst)->content)))
		{
			token->type = token_op;
			op_token->type = op_pipe;
			break;
		}
		nodes_cpy = nodes_cpy->next;
	}
	return (args_lst);
}

char	*ft_check_paths(char *cmdname, t_list *envp)
{
	char	*temp;
	char	**paths;
	int		i;

	temp = ft_dictmap(envp, "PATH");
	if (!temp)
		return (NULL);
	paths = ft_split_gc(temp, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin_mult_gc(3, paths[i], "/", cmdname);
		if (!access(temp, X_OK))
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

char	*ft_get_cmdpath(char *cmd, t_list *envp)
{
	char	*path;
	char	*err;

	if (ft_ispath(cmd))
		return (ft_parse_path(cmd, envp));
	path = ft_check_paths(cmd, envp);
	if (path)
		return (path);
	err = ft_strjoin_gc(cmd, ": command not found \n");
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

t_list	*ft_parse_cmd_args(t_string_compound_lst *tokens, t_shell_data *data)
{
	t_list	*args;
	char	*arg;
	char	*joined;
	char	*temp;

	args = NULL;
	joined = NULL;
	while (tokens)
	{
		if (tokens->type == word_replace_vars)
		{
			arg = ft_wordtostr(tokens->str, data);
			if (!args && ft_str_hasspace(arg))
				args = ft_separate_cmdname(arg);
			else
			{
				temp = joined;
				joined = ft_strjoin_gc(joined, arg);
				ft_free(temp);
			}
		}
		else if (tokens->type == word_true)
		{
			temp = joined;
			joined = ft_strjoin_gc(joined, tokens->str);
			ft_free(temp);
		}
		tokens = tokens->next;
	}
	if (joined)
		ft_lstadd_back(&args, ft_lstnew_gc(joined));
	return (args);
}
