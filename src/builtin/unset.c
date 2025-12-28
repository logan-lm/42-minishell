/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:13:50 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/28 11:06:53 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_shell_data *data, int fdout)
{
	if (fdout != STDOUT_FILENO)
		close(fdout);
	args++;
	while (*args)
	{
		ft_dictdel(&data->envp, *args);
		ft_dictdel(&data->vars, *args);
		args++;
	}
	return (1);
}
