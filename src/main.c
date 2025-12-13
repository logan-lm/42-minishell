/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:11:10 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/13 12:06:33 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*prompt;
	char			**args;
	t_shell_data	s_data;
	t_dict			*var;

	(void)ac;
	(void)av;
	ft_bzero(&s_data, sizeof(t_shell_data));
	ft_parse_envp(envp, &s_data.envp);
	var = s_data.envp->content;
	printf("%s\n", ft_dictmap(s_data.envp, "LANGUAGE"));
	while (1)
	{
		prompt = readline("ho ho ho>");
		ft_add_exit(prompt, free);
		args = ft_split(prompt, ' ');
		ft_echo(args + 1);
		add_history(prompt);
	}
}
