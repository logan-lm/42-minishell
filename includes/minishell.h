/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:49:07 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/17 15:02:43 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "parser.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <errno.h>
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
char		*ft_parse_path(char *path, t_shell_data *s_data);
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
void		cd(char *path, t_shell_data *s_data);

//// PARSING
void		ft_parse_envp(char **envp, t_list **enpv_list);

#endif
