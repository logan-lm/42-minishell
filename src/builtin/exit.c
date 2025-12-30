/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:39:16 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/30 17:49:15 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_shell_exit(char **args, t_shell_data *data, int fdin, int fdout)
{
	(void)args;
	close(fdin);
	close(fdout);
	while (wait(NULL) > 0)
		;
	ft_putstr_fd("exit\n", 1);
	ft_exit(data->exit_status);
}