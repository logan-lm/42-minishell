/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:41:16 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/22 09:34:32 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_envp(char **envp, t_shell_data *data)
{
	char		**part;

	while (*envp)
	{
		part = ft_split_gc(*envp, '=');
		ft_dictadd(&data->envp, part[0], part[1]);
		envp++;
	}
	data->pwd = ft_getenv(data->envp, "PWD");
	if (!*data->pwd)
	{
		data->pwd = getcwd(NULL, 0);
		ft_dictadd(&data->envp, "PWD", data->pwd);
	}
}
