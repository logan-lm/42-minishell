/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:02:31 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 17:09:32 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

int	main(int ac, char **av, char **envp)
{
	t_shell_data		d;

	(void)ac;
	g_sig = 0;
	ft_bzero(&d, sizeof(t_shell_data));
	ft_init_envp(av, envp, &d);
	//d.sa.sa_handler = ft_sig_handler;
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		ft_readline(&d);
}
