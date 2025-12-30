/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/30 22:23:43 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"

t_list	*ft_separate_cmdname(char *arg)
{
	char	*temp;
	int		i;
	int		j;
	t_list	*args;

	temp = ft_calloc_gc(ft_strclen(arg, ' '), sizeof(char));
	i = 0;
	j = 0;
	args = NULL;
	while (arg[j] != ' ')
		temp[i++] = arg[j++];
	temp[i] = '\0';
	ft_lstadd_front(&args, ft_lstnew_gc(temp));
	while (arg[j] == ' ')
		j++;
	temp = ft_calloc_gc(ft_strlen(temp + j), sizeof(char));
	i = 0;
	while (arg[j])
		temp[i++] = arg[j++];
	temp[i] = '\0';
	ft_lstadd_back(&args, ft_lstnew_gc(temp));
	return (args);
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
		if (*cmd == '=' || (*cmd == '+' && *(cmd + 1) == '='))
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
	if (!ft_strncmp(cmd, "exit", 6))
		return (ft_shell_exit);
	if (!ft_strncmp(cmd, "()", 3))
		return (ft_subshell);
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

int	ft_run_builtin(int(builtin)(char **, t_shell_data *, int fdin, int fdout),
		t_command *cmd, t_shell_data *data, void *next, int fdin)
{
	int fdout;
	int exit_status;
	int pipefd[2];

	fdout = cmd->fdout;
	pipe(pipefd);
	if (next && fdout == STDOUT_FILENO)
		fdout = pipefd[1];
	else
		close(pipefd[1]);
	exit_status = builtin(cmd->args, data, fdin, fdout);
	// HANDLE FUNCTION ERROR
	if (!next)
		return (exit_status);
	return (pipefd[0]);
}

int	ft_run_cmd(int fdin, t_command *cmd, t_shell_data *data, void *next)
{
	int		pid;
	int		pipefd[2];
	void	*cmdpath;

	cmdpath = ft_get_builtin(cmd->args[0]);
	if (cmdpath)
		return (ft_run_builtin(cmdpath, cmd, data, next, fdin));
	if (ft_strncmp(cmd->args[0], "FAILED_OPEN", 12))
		cmdpath = ft_cmd_path(cmd->args[0], data->envp);
	pipe(pipefd);
	if ((!next || cmd->fdout != STDOUT_FILENO) && !close(pipefd[1]))
		pipefd[1] = cmd->fdout;
	if (!ft_strncmp(cmd->args[0], "FAILED_OPEN", 12) || !cmdpath)
	{
		if (pipefd[1] != STDOUT_FILENO)
			close(pipefd[1]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		dup2(fdin, 0);
		execve(cmdpath, cmd->args, ft_str_env(data->envp));
		ft_print_perror("", data->progname);
		exit (127);
	}
	if (fdin != STDIN_FILENO && fdin != STDOUT_FILENO)
		close(fdin);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
	if (!next)
	{
		close(pipefd[0]);
		waitpid(pid, &data->exit_status, 0);
		return (WEXITSTATUS(data->exit_status));
	}
	return (pipefd[0]);
}

int	ft_run_cmds(t_list *commands, t_shell_data *d)
{
	int			fd_in;
	t_command	*cmd;

	fd_in = STDIN_FILENO;
	while (commands)
	{
		cmd = commands->content;
		if (cmd->fdin != STDIN_FILENO)
		{
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			fd_in = cmd->fdin;
		}
		fd_in = ft_run_cmd(fd_in, cmd, d, commands->next);
		commands = commands->next;
	}
	while (wait(NULL) > 0)
		;
	return (fd_in);
}

char	**ft_parse_cmd(t_list *nodes, t_shell_data *d)
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;
	t_list			*args_lst;

	args_lst = NULL;
	while (nodes)
	{
		token = nodes->content;
		if (token->type == token_op)
		{
			op_token = token->data;
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
		nodes = nodes->next;
	}
	return (ft_lsttostrs(args_lst));
}

int	ft_run_pipeline(t_command_node *command_tree, t_shell_data *d)
{
	int			has_pipe;
	t_list		*commands;
	t_command	*cmd;

	commands = NULL;
	has_pipe = 1;
	while (command_tree->commands && has_pipe)
	{
		cmd = ft_calloc_gc(1, sizeof(t_command));
		cmd->args = ft_parse_cmd(command_tree->commands, d);
		cmd->fdin = ft_parse_fdin(command_tree->commands, d);
		cmd->fdout = ft_parse_fdout(command_tree->commands, d);
		if (cmd->fdin < 0 || cmd->fdout < 0)
			cmd->args[0] = "FAILED_OPEN";
		ft_lstadd_back(&commands, ft_lstnew_gc(cmd));
		has_pipe = ft_has_pipe(command_tree->commands);
		if (has_pipe)
			command_tree->commands = ft_next_cmd(command_tree->commands);
	}
	return(ft_run_cmds(commands, d));
	//ft_lstclear_gc(&commands);
}

int	ft_exec(t_command_node *command_tree, t_shell_data *d)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
	d->lines++;
	if (command_tree->type == command_pipeline)
		exit_status = ft_run_pipeline(command_tree, d);
	if (command_tree->type == command_and)
		exit_status = ft_and(command_tree, d);
	if (command_tree->type == command_or)
		exit_status = ft_or(command_tree, d);
	while (wait(NULL) > 0)
		;
	return (exit_status);
}
