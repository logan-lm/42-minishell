/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:29:50 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/22 14:30:10 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_int_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_readline(void)
{
	char	*prompt;
	t_list	*token_lst;

	prompt = readline("\001\033[1;32m\002Minishell>\001\033[0m\002");
	if (prompt == NULL)
		ft_exit(EXIT_SUCCESS);
	if (ft_strcmp(prompt, "gc") == 0)
		ft_gc_print_count();
	add_history(prompt);
	token_lst = ft_get_tokens(prompt);
	ft_print_token(token_lst);
	if (token_lst)
		ft_free_token_list(token_lst);
	ft_add_exit(prompt, free);
}
