/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:56:23 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/13 18:01:03 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **args, t_shell_data *s_data)
{
	if (!*args)
		ft_dictadd(&s_data->envp, "PWD", ft_dictmap(s_data->envp, "HOME"));
	else if (!access(*args, R_OK))
		ft_dictadd(&s_data->envp, "PWD", *args);
	else
		perror("minishell ");
}
