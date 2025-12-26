/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:02:31 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/26 22:09:39 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell_data	d;

	(void)ac;
	(void)av;
	ft_bzero(&d, sizeof(t_shell_data));
	ft_init_envp(envp, &d);
	//ft_pwd(NULL, &d);
	ft_dictadd(&d.envp, "CAT", "echo");
	//ft_putstr_fd(ft_wordtostr("$PWD$B$HOME$HOME$HOME$HOME$HOME$HOME.$HOMER.", &d), 1);
	ft_putchar_fd('\n', 1);
	signal(SIGINT, ft_int_handler);
	char **cmd = ft_split_gc(ft_wordtostr("$CAT", &d), ' ');
	ft_printf("%s\n", ft_cmd_path(cmd[0], d.envp));                 
	while (1)
	{
		ft_readline(&d);
	}
}
