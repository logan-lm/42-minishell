/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:02:31 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/23 10:38:38 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell_data	d;
	t_list			*cmds;

	(void)ac;
	(void)av;
	cmds = NULL;
	ft_bzero(&d, sizeof(t_shell_data));
	ft_init_envp(envp, &d);
	ft_pwd(NULL, &d);
	signal(SIGINT, ft_int_handler);
	while (1)
	{
		ft_readline(&d);
		ft_exec(cmds, &d);
	}
}
