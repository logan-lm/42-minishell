/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:20 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/27 09:45:30 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include "parser.h"

void	ft_test_cmds(t_list **cmds)
{
	t_token_op_data			*subshell_token_in;
	t_string_compound_lst	*subshell_list_in;
	t_token_op_data			*subshell_token_out;
	t_string_compound_lst	*subshell_list_out;
	t_command_node			*subshell;
	t_command_node			*and;
	t_token_op_data			*cat1_token;
	t_string_compound_lst	*cat1_list;
	t_command_node			*cat1;
	t_token_op_data			*cat2_token;
	t_string_compound_lst	*cat2_list;
	t_token_op_data			*cat2_token_redir;
	t_string_compound_lst	*cat2_list_redir;
	t_command_node			*cat2;

	// SUBSHELL
	subshell_token_in = ft_malloc(sizeof(t_token_op_data));
	subshell_token_in->type = op_in_redirect;
	subshell_list_in = ft_malloc(sizeof(t_string_compound_lst));
	subshell_list_in->next = NULL;
	subshell_list_in->str = "infile";
	subshell_list_in->type = word_replace_vars;
	subshell_token_in->word = subshell_list_in;
	subshell_token_out = ft_malloc(sizeof(t_token_op_data));
	subshell_token_out->type = op_out_redirect_trunc;
	subshell_list_out = ft_malloc(sizeof(t_string_compound_lst));
	subshell_list_out->next = NULL;
	subshell_list_out->str = "outfile";
	subshell_list_out->type = word_replace_vars;
	subshell_token_out->word = subshell_list_out;
	subshell = ft_malloc(sizeof(t_command_node));
	subshell->type = command_subshell;
	subshell->right = NULL;
	ft_lstadd_back(&subshell->commands, ft_lstnew(subshell_token_in));
	ft_lstadd_back(&subshell->commands, ft_lstnew(subshell_token_out));
	// AND
	and = ft_malloc(sizeof(t_command_node));
	and->type = command_and;
	and->commands = NULL;
	subshell->left = and;
	// CAT1
	cat1_token = ft_malloc(sizeof(t_token_op_data));
	cat1_token->type = op_pipe;
	cat1_list = ft_malloc(sizeof(t_string_compound_lst));
	cat1_list->next = NULL;
	cat1_list->str = "cat";
	cat1_list->type = word_replace_vars;
	cat1_token->word = cat1_list;
	cat1 = ft_malloc(sizeof(t_command_node));
	cat1->type = command_pipeline;
	cat1->left = NULL;
	cat1->right = NULL;
	ft_lstadd_back(&cat1->commands, ft_lstnew(cat1_token));
	and->left = cat1;
	// CAT2
	cat2_token = ft_malloc(sizeof(t_token_op_data));
	cat2_token->type = op_pipe;
	cat2_list = ft_malloc(sizeof(t_string_compound_lst));
	cat2_list->next = NULL;
	cat2_list->str = "$CAT";
	cat2_list->type = word_replace_vars;
	cat2_token->word = cat2_list;
	cat2_token_redir = ft_malloc(sizeof(t_token_op_data));
	cat2_token_redir->type = op_out_redirect_trunc;
	cat2_list_redir = ft_malloc(sizeof(t_string_compound_lst));
	cat2_list_redir->next = NULL;
	cat2_list_redir->str = "testa";
	cat2_list_redir->type = word_replace_vars;
	cat2_token_redir->word = cat2_list_redir;
	cat2 = ft_malloc(sizeof(t_command_node));
	cat2->type = command_pipeline;
	cat2->left = NULL;
	cat2->right = NULL;
	ft_lstadd_back(&cat2->commands, ft_lstnew(cat2_token));
	ft_lstadd_back(&cat2->commands, ft_lstnew(cat2_token_redir));
	and->right = cat2;
	ft_lstadd_back(cmds, ft_lstnew(subshell));
}

char	*parse_cmd_args(t_string_compound_lst *tokens, t_shell_data *data)
{
	char	*joined;
	char	*temp;

	joined = NULL;
	while (tokens)
	{
		if (tokens->type == word_replace_vars)
		{
			temp = joined;
			joined = ft_strjoin_mult_gc(3, joined, " ",
					ft_wordtostr(tokens->str, data));
		}
		else if (tokens->type == word_true)
		{
			temp = joined;
			joined = ft_strjoin_mult_gc(3, joined, " ", tokens->str);
			free(joined);
		}
		free(temp);
		tokens = tokens->next;
	}
	return (joined);
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
		if (!ft_isalnum(*cmd))
			return (0);
		if (*cmd == '=')
			return (1);
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
	free(temp);
	while (paths[i])
	{
		temp = ft_strjoin_mult_gc(3, paths[i], "/", cmdname);
		if (!access(temp, X_OK))
		{
			ft_free_strs(paths);
			return (temp);
		}
		free (temp);
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
	if (ft_get_builtin(cmd))
		return("builtin");
	path = ft_check_paths(cmd, envp);
	if (path)
		return (path);
	err = ft_strjoin_gc(cmd, ": command not found \n");
	ft_putstr_fd(err, 2);
	ft_free(err);
	return (NULL);
}

void	ft_exec(t_list *cmds, t_shell_data *d)
{
	t_list					*top;
	t_command_node			*cmd;
	t_list					*cat_lst;
	t_token_op_data			*cat_token;
	t_string_compound_lst	*cat_cmpd;
	char					*joined;
	char					*temp;
	char					**strs;

	(void)d;
	ft_test_cmds(&cmds);
	top = cmds;
	cmd = top->content;
	cat_lst = cmd->left->right->commands;
	cat_token = cat_lst->content;
	cat_cmpd = cat_token->word;
	joined = NULL;
	while (cat_lst)
	{
		cat_token = cat_lst->content;
		cat_cmpd = cat_token->word;
		if (cat_token->type == op_pipe)
		{
			temp = ft_strjoin_gc(joined, parse_cmd_args(cat_cmpd, d));
			free(joined);
			joined = temp;
		}
		cat_lst = cat_lst->next;
	}
	strs = ft_split_gc(joined, ' ');
	while (*strs)
	{
		ft_putchar_fd('>', 1);
		ft_putstr_fd(*(strs++), 1);
		ft_putchar_fd('\n', 1);
	}
	/*while (*top)
	{
		cmd = top->content;
		if (cmd->type == op_pipe)
		{
			cmd->
		}
		top = top->next;
	}*/
}
