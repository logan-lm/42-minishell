/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:44:59 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/12 11:10:22 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parse_args(char **args, t_echo_data *data)
{
	t_list *strs;
	t_list *new;

	strs = NULL;
	while (*args)
	{
		if (!strncmp("-n", *args, 3))
			data->no_newline = 1;
		else
		{
			new = ft_lstnew(*args);
			if (!new)
			{
				//HANDLE ERROR
			}
			ft_lstadd_back(&strs, new);
		}
		args++;
	}
	return (strs);
}

void	echo(char **args)
{
	t_echo_data	data;
	t_list		*strs;
	t_list		*temp;

	strs = parse_args(args, &data);
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
}
