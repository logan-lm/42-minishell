/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:25:23 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/21 22:31:51 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_shell_data *data)
{
	t_list	*envp;
	t_dict	*var;

	(void)args;
	envp = data->envp;
	while (envp)
	{
		var = envp->content;
		printf("%s=%s\n", var->key, var->value);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}