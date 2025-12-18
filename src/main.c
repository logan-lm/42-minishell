/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:11:10 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/18 10:49:46 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_token(t_list *token_lst)
{
	t_parsing_token			*parsing_token;
	t_string_compound_lst	*lst;

	while (token_lst)
	{
		parsing_token = (t_parsing_token *)token_lst->content;
		if (parsing_token->type == token_end)
			printf("[end]\n");
		else if (parsing_token->type == token_op)
		{
			printf("[operator: %d]\n", *((int *)parsing_token->data));
		}
		else if (parsing_token->type == token_literal)
		{
			printf("[literal]\n");
			lst = (t_string_compound_lst *)parsing_token->data;
			while (lst)
			{
				printf("\t%d:%s\n", lst->type, lst->str);
				lst = lst->next;
			}
		}
		token_lst = token_lst->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	char			*prompt;
	t_shell_data	d;
	t_list			*token_lst;

	(void)ac;
	(void)av;
	ft_bzero(&d, sizeof(t_shell_data));
	ft_parse_envp(envp, &d.envp);
	while (1)
	{
		prompt = readline("\033[1;32mMinishell>\033[0m");
		token_lst = ft_get_tokens(prompt);
		ft_print_token(token_lst);
		ft_free_token_list(token_lst);
		add_history(prompt);
		ft_add_exit(prompt, free);
	}
}
