/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:34:09 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/28 18:10:26 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_and(t_command_node *command_tree, t_shell_data *data)
{
	int exit_status;
	
	exit_status = ft_exec(command_tree->left, data);
	if (exit_status)
		return (exit_status);
	return (ft_exec(command_tree->right, data));
}

int	ft_or(t_command_node *command_tree, t_shell_data *data)
{
	int exit_status;
	
	exit_status = ft_exec(command_tree->left, data);
	if (exit_status)
		return (ft_exec(command_tree->right, data));
	return (exit_status);
}

int	ft_subshell(t_command_node *command_tree, t_shell_data *data)
{
	int exit_status;
	int pid;

	exit_status = 0;
	pid = fork();
	if (pid == 0)
		exit(ft_exec(command_tree->left, data));
	waitpid(pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}