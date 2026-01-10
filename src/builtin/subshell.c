/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:13:50 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 20:22:08 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_subshell(char **args, t_shell_data *data, int fdin, int fdout)
{
	int	pid;
	int	status;
	int	ret;

	args++;
	pid = fork();
	if (pid == 0)
	{
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
		ft_exit(ret);
	}
	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
