/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:34:09 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/30 14:11:23 by lomartin         ###   ########.fr       */
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
