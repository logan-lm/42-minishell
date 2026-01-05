/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 21:53:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 18:01:56 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_perror(char *err, char *progname)
{
	char	*str;

	str = ft_strjoin_mult_gc_id(malloc_id_exec, 3, progname, ": ", err);
	perror(str);
	ft_free(str);
	return (EXIT_FAILURE);
}

int	ft_print_error(char *err, char *progname)
{
	char	*str;

	str = ft_strjoin_mult_gc_id(malloc_id_exec, 4, progname, ": ", err, "\n");
	ft_putstr_fd(str, 2);
	ft_free(str);
	return (EXIT_FAILURE);
}
