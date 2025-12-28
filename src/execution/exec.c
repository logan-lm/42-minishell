/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/28 21:52:02 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "exec.h"
#include "minishell.h"
#include "parser.h"

t_list	*ft_parse_cmd_args(t_string_compound_lst *tokens, t_shell_data *data)
{
	t_list	*args;

	args = NULL;
	while (tokens)
	{
		if (tokens->type == word_replace_vars)
			ft_lstadd_back(&args, ft_lstnew(ft_wordtostr(tokens->str, data)));
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

int	ft_run_builtin(int(builtin)(char **, t_shell_data *, int fdout),
		t_command *cmd, t_shell_data *data, void *next)
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
	exit_status = builtin(cmd->args, data, fdout);
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
	int		exit_status;

	cmdpath = ft_get_builtin(cmd->args[0]);
	if (cmdpath)
		return (ft_run_builtin(cmdpath, cmd, data, next));
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
		perror("minishell: ");
		exit (127);
	}
	if (fdin != STDIN_FILENO && fdin != STDOUT_FILENO)
		close(fdin);
	if (pipefd[1] != STDOUT_FILENO)
		close(pipefd[1]);
	if (!next)
	{
		close(pipefd[0]);
		waitpid(pid, &exit_status, 0);
		return (WEXITSTATUS(exit_status));
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
	while (has_pipe)
	{
		cmd = ft_calloc_gc(1, sizeof(t_command));
		cmd->args = ft_parse_cmd(command_tree->commands, d);
		cmd->fdin = ft_parse_fdin(command_tree->commands, d);
		cmd->fdout = ft_parse_fdout(command_tree->commands, d);
		if (cmd->fdin < 0 || cmd->fdout < 0)
		{
			cmd->args[0] = "FAILED_OPEN";
		}
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
	if (command_tree->type == command_pipeline)
		exit_status = ft_run_pipeline(command_tree, d);
	if (command_tree->type == command_and)
		exit_status = ft_and(command_tree, d);
	if (command_tree->type == command_or)
		exit_status = ft_or(command_tree, d);
	if (command_tree->type == command_subshell)
		exit_status = ft_subshell(command_tree, d);
	while (wait(NULL) > 0)
		;
	return (exit_status);
}
