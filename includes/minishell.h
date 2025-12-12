/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:49:07 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/12 11:04:26 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

//// BUILT-INS
// ECHO
typedef struct s_echo_data
{
	char	no_newline;
}			t_echo_data;

// BUILT-INS
void		echo(char **args);

#endif
