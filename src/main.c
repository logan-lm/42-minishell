/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:11:10 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/14 17:41:51 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*prompt;
	char			**args;
	t_shell_data	s_data;

	(void)ac;
	(void)av;
	ft_bzero(&s_data, sizeof(t_shell_data));
	ft_parse_envp(envp, &s_data.envp);
	s_data.pwd = ft_dictmap(s_data.envp, "PWD");
	while (1)
	{
		ft_printf("%s\n", ft_dictmap(s_data.envp, "PWD"));
		prompt = readline("\033[1;32mMinishell>\033[0m");
		ft_add_exit(prompt, free);
		args = ft_split(prompt, ' ');
		cd(ft_parse_path(args[1], &s_data), &s_data);
		add_history(prompt);
	}
}
