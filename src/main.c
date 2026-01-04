/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:02:31 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/04 20:17:17 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;

int	main(int ac, char **av, char **envp)
{
	t_shell_data		d;

	(void)ac;
	g_pid = 0;
	ft_bzero(&d, sizeof(t_shell_data));
	ft_init_envp(av, envp, &d);
	// ft_bzero(&d.term, sizeof(d.term));
	// tcgetattr(STDIN_FILENO, &d.term);
	// d.term.c_cc[VQUIT] = _POSIX_VDISABLE;
	// tcsetattr(STDIN_FILENO, TCSANOW, &d.term);
	// ft_bzero(&d.sa, sizeof(d.sa));
	d.sa.sa_handler = ft_sig_handler;
	sigaction(SIGINT, &d.sa, NULL);
	//signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		ft_readline(&d);
}
