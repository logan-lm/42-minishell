/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:11:10 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/18 15:09:02 by pberne           ###   ########.fr       */
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
	ft_parse_envp(envp, &d.envp);
	cd(NULL, &d);
	printf("%s\n", ft_dictmap(d.envp, "PWD"));
	while (1)
	{
		prompt = readline("\033[1;32mMinishell>\033[0m");
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
