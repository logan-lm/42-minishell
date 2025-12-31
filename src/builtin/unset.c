/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:13:50 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/31 14:15:00 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_shell_data *data, int fdin, int fdout)
{
	if (fdin != STDIN_FILENO)
		close(fdin);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	args++;
	while (*args)
	{
		ft_dictdel(&data->envp, *args);
		ft_dictdel(&data->vars, *args);
		args++;
	}
	return (0);
}
