/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:39:25 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/21 21:08:41 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_shell_data *data)
{
	char	*home;

	(void)args;
	home = ft_dictmap(data->envp, "PWD");
	if (home)
		printf("%s\n", home);
	else
		printf("%s\n", data->pwd);
	return (0);
}
