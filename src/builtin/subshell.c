/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:13:50 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/30 16:24:09 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_subshell(char **args, t_shell_data *data, int fdin, int fdout)
{
	int	pid;
	
	args++;
	pid = fork();
	if (pid == 0)
	{
		dup2(fdin, 0);
		dup2(fdout, 1);
		exit (ft_exec((t_command_node *)args[0], data));
	}
	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	return (0);
}
