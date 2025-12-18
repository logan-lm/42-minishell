/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:44:59 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/18 15:13:40 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_parse_args(char **args, t_echo_data *data)
{
	t_list	*strs;
	t_list	*new;

	strs = NULL;
	if (!strncmp("-n", *args, 3))
	{
		data->no_newline = 1;
		args++;
	}
	while (*args)
	{
		new = ft_lstnew_gc(*args);
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
void	ft_echo(char **args)
{
	t_echo_data	data;
	t_list		*strs;
	t_list		*temp;

	data.no_newline = 0;
	strs = ft_parse_args(args, &data);
	while (strs)
	{
		printf("%s", (char *)strs->content);
		temp = strs;
		strs = strs->next;
		if (strs)
			printf(" ");
		free(temp);
	}
	if (!data.no_newline)
		printf("\n");
	exit (1);
}
