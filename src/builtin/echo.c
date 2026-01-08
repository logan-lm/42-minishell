/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/* 
                                                   +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:44:59 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 11:23:02 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_parse_args(char **args, t_echo_data *data)
{
	t_list	*strs;
	t_list	*new;

	strs = NULL;
	while (*args && !strncmp("-n", *args, 3))
	{
		data->no_newline = 1;
		args++;
	}
	while (*args)
	{
		new = ft_lstnew_gc_id(*args, malloc_id_exec);
		ft_lstadd_back(&strs, new);
		args++;
	}
	return (strs);
}

//
// @brief Takes strings as a pointer on strings and writes on STDOUT
// @param args pointers on strings as echo command arguments (-n in first arg)
// @return void
//
int	ft_echo(char **args, t_shell_data *s_data, int fdin, int fdout)
{
	t_echo_data	data;
	t_list		*strs;
	t_list		*temp;

	if (fdin != STDIN_FILENO)
		close(fdin);
	(void)s_data;
	args++;
	data.no_newline = 0;
	strs = ft_parse_args(args, &data);
	while (strs)
	{
		ft_putstr_fd((char *)strs->content, fdout);
		temp = strs;
		strs = strs->next;
		if (strs)
			ft_putchar_fd(' ', fdout);
		ft_free(temp);
	}
	if (!data.no_newline)
		ft_putchar_fd('\n', fdout);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	return (EXIT_SUCCESS);
}
