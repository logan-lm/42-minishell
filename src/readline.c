/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:29:50 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/22 19:47:06 by lomartin         ###   ########.fr       */
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

void	ft_readline(t_shell_data *d)
{
	char	*prompt;
	t_list	*token_lst;

	(void)d;
	prompt = readline("\001\033[1;32m\002Minishell>\001\033[0m\002");
	if (prompt == NULL)
		ft_exit(EXIT_SUCCESS);
	add_history(prompt);
	if (BUILD_DEBUG)
		ft_gc_debug(prompt);
	else
		ft_add_exit(prompt, free);
	token_lst = ft_get_tokens(prompt);
	ft_print_token(token_lst, 0);
	if (token_lst)
		ft_clear_gc_id(malloc_id_token);
}
