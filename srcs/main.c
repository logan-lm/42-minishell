/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:11:10 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/12 11:07:01 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	char	**args;

	while (1)
	{
		prompt = readline("ho ho ho>");
		args = ft_split(prompt, ' ');
		echo(args + 1);
		add_history(prompt);
	}
}
