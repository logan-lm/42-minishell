/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/27 19:23:39 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include "parser.h"

t_list	*ft_parse_cmd_args(t_string_compound_lst *tokens, t_shell_data *data)
{
	t_list	*args;

	args = NULL;
	while (tokens)
	{
		if (tokens->type == word_replace_vars)
		{
			ft_lstadd_back(&args, ft_lstnew(ft_wordtostr(tokens->str, data)));
		}
		else if (tokens->type == word_true)
			ft_lstadd_back(&args, ft_lstnew(tokens->str));
		tokens = tokens->next;
	}
	return (args);
}

int	exec_cmd(char **args, char **envp, int fd_in, int fd_out)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		execve(args[0], args, envp);
		perror("minishell: ");
	}
	close(fd_in);
	return (pid);
}

int	ft_ispath(char *str)
{
	while (*str)
	{
		if (*(str++) == '/')
			return (1);
	}
	return (0);
}

int	ft_is_varset(char *cmd)
{
	if (!ft_isalpha(*cmd) && *(cmd + 1))
		return (0);
	cmd++;
	while (*cmd)
	{
		if (*cmd == '=')
			return (1);
		if (!ft_isalnum(*cmd))
			return (0);
		cmd++;
	}
	return (0);
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
	if (ft_is_varset(cmd))
		return (ft_set_var);
	return (NULL);
}

char	*ft_check_paths(char *cmdname, t_list *envp)
{
	char	*temp;
	char	**paths;
	int		i;

	temp = ft_dictmap(envp, "PATH");
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

char	*ft_cmd_path(char *cmd, t_list *envp)
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

void	ft_run_builtin(void *(builtin)(char **, t_shell_data *), char **args,
		t_shell_data *data)
{
	builtin(args, data);
}

int	ft_run_cmd(char **args, char **envp, t_shell_data *data)
{
	int		pid;
	void	*cmdpath;

	cmdpath = ft_get_builtin(args[0]);
	if (cmdpath)
	{
		ft_run_builtin(cmdpath, args, data);
		return (0);
	}
	cmdpath = ft_cmd_path(args[0], data->envp);
	pid = fork();
	if (pid == 0)
	{
		execve(cmdpath, args, envp);
		exit(1);
	}
	return (pid);
}

void	ft_run_pipeline(t_command_node *command_tree, t_shell_data *d)
{
	t_list			*nodes;
	t_parsing_token	*token;
	t_token_op_data	*test;
	t_list			*args_lst;
	char			**args;

	args_lst = NULL;
	args = NULL;
	nodes = command_tree->commands;
	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			test = token->data;
			if (test->type == op_pipe)
				break ;
		}
		if (token->type == token_word)
			args_lst = ft_lstmerge(args_lst, ft_parse_cmd_args(token->data, d));
		nodes = nodes->next;
	}
	args = ft_lsttostrs(args_lst);
	if (args)
		ft_run_cmd(args, ft_str_env(d->envp), d);
}

void	ft_exec(t_command_node *command_tree, t_shell_data *d)
{
	if (command_tree->type == command_pipeline)
		ft_run_pipeline(command_tree, d);
	while (wait(NULL) > 0)
		;
}
