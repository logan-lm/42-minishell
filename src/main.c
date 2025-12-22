/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:02:31 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/23 10:28:16 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*prompt;
	t_shell_data	d;
	t_list			*token_lst;

	(void)ac;
	(void)av;
	ft_bzero(&d, sizeof(t_shell_data));
	ft_init_envp(envp, &d);
	ft_pwd(NULL, &d);
	while (1)
	{
		prompt = readline("\001\033[1;32m\002Minishell>\001\033[0m\002");
		if (prompt == NULL)
			ft_exit(EXIT_SUCCESS);
		add_history(prompt);
		token_lst = ft_get_tokens(prompt);
		ft_print_token(token_lst);
		if (token_lst)
			ft_free_token_list(token_lst);
		ft_add_exit(prompt, free);
	}
}
