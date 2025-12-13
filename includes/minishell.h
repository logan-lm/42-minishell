/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:49:07 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/13 17:49:14 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_shell_data
{
	char	*pwd;
	t_list	*envp;
}			t_shell_data;

typedef struct s_dict
{
	char	*key;
	char	*value;
}			t_dict;

// UTILS
char		*ft_dictmap(t_list *list, char *key);
void		ft_dictadd(t_list **list, char *key, char *value);
t_dict		*ft_dictpop(t_list **list, char *key);

void		ft_echo(char **args);

//// BUILT-INS
// ECHO
typedef struct s_echo_data
{
	char	no_newline;
}			t_echo_data;

void		ft_echo(char **args);
void		cd(char **args, t_shell_data *s_data);

//// PARSING
void		ft_parse_envp(char **envp, t_list **enpv_list);

#endif
