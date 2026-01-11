/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:49:07 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 21:30:55 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "command.h"
# include "libft.h"
# include "parser.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

# ifndef BUILD_DEBUG
#  define BUILD_DEBUG 0
# endif

extern int				g_sig;

typedef struct s_shell_data
{
	char				*progname;
	char				**argv;
	t_list				*envp;
	t_list				*vars;
	int					exit_status;
	int					lines;
	char				*wc_path;
	struct sigaction	sa;
	t_list				*opened_hd;
	int					interactive;
}						t_shell_data;

typedef struct s_dict
{
	char				*key;
	char				*value;
}						t_dict;

// UTILS
char					*ft_parse_path(char *path, t_list *envp);
char					*ft_getenv(t_list *envp, char *key);
char					*ft_getvar(t_list *vars, t_list *envp, char **args,
							char *key);
char					*ft_dictmap(t_list *list, char *key);
void					ft_dictadd(t_list **list, char *key, char *value);
t_dict					*ft_dictpop(t_list **list, char *key);
void					ft_dictdel(t_list **list, char *key);
void					ft_free_strs(char **strs);
char					**ft_lsttostrs(t_list *lst);
int						ft_is_varset(char *cmd);
int						ft_print_perror(char *err, char *progname);
int						ft_print_error(char *err, char *progname);
int						ft_getpid(void);
void					ft_setpid(int pid);
int						ft_getfd(void);
void					ft_setfd(int fd);
int						ft_gethd(void);
void					ft_sethd(int hd);
char					ft_isdir(char *path);
void					ft_unlink_hds(t_shell_data *data);
char					*ft_get_prompt(void);
void					ft_sig_hd_handler(int sig);

void					ft_gc_debug(char *str);

// READLINE
void					ft_sig_handler(int sig);
void					ft_readline(t_shell_data *d);

// EXEC
int						ft_exec(t_command_node *command_tree, t_shell_data *d);
t_list					*ft_wordtostr(char *word, t_list **src,
							t_shell_data *data, void *next);
void					*ft_get_builtin(char *cmd);
char					*ft_check_paths(char *cmdname, t_list *envp);
char					*ft_cmd_path(char *cmd, t_list *envp);
int						ft_run_cmds(t_list *commands, t_shell_data *d);
t_list					*ft_parse_cmd_args(t_string_compound_lst *tokens,
							t_shell_data *data);

//// BUILT-INS
// ECHO
typedef struct s_echo_data
{
	char				no_newline;
}						t_echo_data;

int						ft_echo(char **args, t_shell_data *data, int fdin,
							int fdout);
int						ft_env(char **args, t_shell_data *data, int fdin,
							int fdout);
int						ft_cd(char **args, t_shell_data *data, int fdin,
							int fdout);
int						ft_pwd(char **args, t_shell_data *data, int fdin,
							int fdout);
int						ft_export(char **args, t_shell_data *data, int fdin,
							int fdout);
int						ft_unset(char **args, t_shell_data *data, int fdin,
							int fdout);
int						ft_set_var(char **args, t_shell_data *data, int fdin,
							int fdout);
int						ft_shell_exit(char **args, t_shell_data *data, int fdin,
							int fdout);

//// PARSING
void					ft_init_envp(char **av, char **envp,
							t_shell_data *data);
char					**ft_str_env(t_list *envp_d);
t_list					*ft_get_matching_names(t_list *src, char *pattern);
int						ft_is_name_character(char c);
int						ft_is_assignement_op(char *str, int *i);

#endif
