/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:13:50 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 10:05:53 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

void	ft_clear_opened_heredocs(t_list *nodes)
{
	t_open_data	o_d;

	while (nodes)
	{
		o_d.token = nodes->content;
		if (o_d.token && o_d.token->type == token_op)
		{
			o_d.op_token = o_d.token->data;
			if (o_d.op_token->type == op_heredoc
				&& o_d.op_token->word->heredoc_fd > 2)
				close(o_d.op_token->word->heredoc_fd);
		}
		nodes = nodes->next;
	}
}

void	ft_subshell_child(char **args, t_shell_data *data, int fdin, int fdout)
{
	int	ret;

	if (fdin != STDIN_FILENO)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	ret = ft_exec((t_command_node *)args[0], data);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	ft_exit(ret);
}

int	ft_subshell(char **args, t_shell_data *data, int fdin, int fdout)
{
	int				pid;
	int				status;
	t_command_node	*command_tree;

	args++;
	pid = fork();
	if (pid == 0)
		ft_subshell_child(args, data, fdin, fdout);
	command_tree = (t_command_node	*)args[0];
	ft_clear_opened_heredocs(command_tree->commands);
	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
