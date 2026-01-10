/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:25:23 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/10 13:28:56 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_shell_data *data, int fdin, int fdout)
{
	t_list	*envp;
	t_dict	*var;

	ft_consume_stdin(fdin);
	(void)args;
	envp = data->envp;
	while (envp)
	{
		var = envp->content;
		ft_putstr_fd(var->key, fdout);
		ft_putchar_fd('=', fdout);
		ft_putstr_fd(var->value, fdout);
		ft_putchar_fd('\n', fdout);
		envp = envp->next;
	}
	if (fdout != STDOUT_FILENO)
		close(fdout);
	return (EXIT_SUCCESS);
}
