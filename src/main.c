/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:02:31 by lomartin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/12/22 17:05:03 by pberne           ###   ########.fr       */
=======
/*   Updated: 2025/12/22 12:16:20 by pberne           ###   ########.fr       */
>>>>>>> f26a64d (test)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell_data	d;
	t_list			*token_lst;

	(void)ac;
	(void)av;
	ft_bzero(&d, sizeof(t_shell_data));
	ft_init_envp(envp, &d);
	ft_pwd(NULL, &d);
	signal(SIGINT, ft_int_handler);
	token_lst = NULL;
	while (1)
	{
		ft_readline();
	}
}
