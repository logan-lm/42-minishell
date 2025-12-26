/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:02:31 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/23 21:42:58 by lomartin         ###   ########.fr       */
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
	//ft_pwd(NULL, &d);
	ft_dictadd(&d.envp, "CAT", "cat -e");
	//ft_putstr_fd(ft_wordtostr("$PWD$B$HOME$HOME$HOME$HOME$HOME$HOME.$HOMER.", &d), 1);
	ft_putchar_fd('\n', 1);
	ft_printf("%p\n", get_builtin("export"));
	signal(SIGINT, ft_int_handler);
	while (1)
	{
		ft_readline(&d);
		ft_exec(cmds, &d);
	}
}
