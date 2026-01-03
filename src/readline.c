/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:29:50 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/03 23:07:56 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_int_handler(int sig)
{
	while (wait(NULL) > 0)
		;
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_split_prompt(char *prompt, t_shell_data *d)
{
	char			**prompt_childs;
	int				i;
	t_list			*token_lst;
	t_command_node	*command_tree;

	prompt_childs = ft_split_gc(prompt, '\n');
	free(prompt);
	i = -1;
	while (prompt_childs[++i])
	{
		add_history(prompt_childs[i]);
		if (BUILD_DEBUG)
			ft_gc_debug(prompt_childs[i]);
		token_lst = ft_get_tokens(prompt_childs[i]);
		command_tree = ft_build_ast(token_lst);
		ft_print_ast_visual(command_tree, "");
		ft_dictadd(&d->vars, "?", ft_itoa_gc(ft_exec(command_tree, d)));
		ft_clear_gc_id(malloc_id_token);
		ft_clear_gc_id(malloc_id_ast);
	}
	ft_free_strs(prompt_childs);
}

void	ft_readline(t_shell_data *d)
{
	char			*prompt;

	prompt = readline("\001\033[1;32m\002Minishell>\001\033[0m\002");
	if (prompt == NULL)
	{
		ft_putstr_fd("exit\n", 1);
		ft_exit(EXIT_SUCCESS);
	}
	if (*prompt == '\0')
		return ;
	ft_split_prompt(prompt, d);
}
