/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:49:07 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/23 21:38:57 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "parser.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>

# ifndef BUILD_DEBUG
#  define BUILD_DEBUG 0
# endif

typedef struct s_shell_data
{
	char	*pwd;
	t_list	*envp;
	t_list	*vars;
}			t_shell_data;

typedef struct s_dict
{
	char	*key;
	char	*value;
}			t_dict;

// UTILS
char		*ft_parse_path(char *path, t_list *envp);
char		*ft_getenv(t_list *envp, char *key);
char		*ft_dictmap(t_list *list, char *key);
void		ft_dictadd(t_list **list, char *key, char *value);
t_dict		*ft_dictpop(t_list **list, char *key);
void		ft_dictdel(t_list **list, char *key);
int			ft_env(char **args, t_shell_data *data);
int			ft_set_var(char **args, t_shell_data *data);

void		ft_gc_debug(char *str);

// READLINE
void		ft_int_handler(int sig);
void		ft_readline(t_shell_data *d);

// EXEC
void		ft_exec(t_list *cmds, t_shell_data *d);
char		*ft_wordtostr(char *word, t_shell_data *data);
void		*get_builtin(char *cmd);

//// BUILT-INS
// ECHO
typedef struct s_echo_data
{
	char	no_newline;
}			t_echo_data;

int			ft_echo(char **args, t_shell_data *data);
int			ft_cd(char **args, t_shell_data *data);
int			ft_pwd(char **args, t_shell_data *data);
int			ft_export(char **args, t_shell_data *data);
int			ft_unset(char **args, t_shell_data *data);

//// PARSING
void		ft_init_envp(char **envp, t_shell_data *data);
char		**ft_str_env(t_list *envp_d);

#endif
