/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_visualizer_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 22:50:17 by pberne            #+#    #+#             */
/*   Updated: 2025/12/25 23:12:07 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_op_name(int op_code)
{
	if (op_code == op_pipe)
		return ("| : pipe");
	if (op_code == op_in_redirect)
		return ("< : redirect IN");
	if (op_code == op_heredoc)
		return (">> : heredoc");
	if (op_code == op_out_redirect_trunc)
		return ("> : redirect OUT TRUNC");
	if (op_code == op_out_redirect_append)
		return (">> : redirect OUT APPEND");
	return ("");
}

void	ft_print_word_content(t_string_compound_lst *lst, char *prefix)
{
	while (lst)
	{
		if (lst->next == NULL)
			ft_printf("%s%s", prefix, "└╴ ");
		else
			ft_printf("%s%s", prefix, "├╴ ");
		ft_printf("(type:%d, is_naked:%d) ", lst->type, lst->is_naked);
		if (lst->is_name)
			ft_printf("[VAR_NAME] ");
		ft_printf(": %s\n", lst->str);
		lst = lst->next;
	}
}

void	ft_print_op_content(char *next_prefix, t_parsing_token *token)
{
	t_token_op_data	*op;

	op = (t_token_op_data *)token->data;
	ft_printf("[%d] %s\n", op->type, ft_get_op_name(op->type));
	if (op->word)
		ft_print_word_content(op->word, next_prefix);
}
