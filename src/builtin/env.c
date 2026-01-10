/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:25:23 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/31 14:14:42 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_shell_data *data, int fdin, int fdout)
{
	t_list	*envp;
	t_dict	*var;

	if (fdin != STDIN_FILENO)
		close(fdin);
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
