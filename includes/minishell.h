/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 10:49:07 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 11:34:56 by pberne           ###   ########.fr       */
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
char					*ft_getenv_gc_id(t_list *envp, char *key, int id);
char					*ft_getvar(t_list *vars, t_list *envp, char **args,
							char *key);
char					*ft_getvar_exec(t_list *vars, t_list *envp, char **args,
							char *key);
// Dict
char					*ft_dictmap(t_list *list, char *key);
char					*ft_dictmap_gc_id(t_list *list, char *key, int id);
void					free_dict_entry(void *entry);
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
char					*ft_get_progname(void);
void					ft_set_progname(char *progname);
char					**ft_join_strs(char *str, char **strs, char *var);
void					ft_gc_debug(char *str);

// READLINE
void					ft_sig_handler(int sig);
void					ft_readline(t_shell_data *d);

// EXEC
int						ft_exec(t_command_node *command_tree, t_shell_data *d);
t_list					*ft_wordtostr(char *word, t_list **src,
							t_shell_data *data, int no_expand);
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
void					ft_print_export_noarg(t_shell_data *data, int fdout);

//// PARSING
void					ft_init_envp(char **av, char **envp,
							t_shell_data *data);
char					**ft_str_env(t_list *envp_d);
t_list					*ft_get_matching_names(t_list *src, char *pattern);
int						ft_is_pattern_matching(char *src, char *pattern);
int						ft_is_pattern_matching_cmpd(char *src,
							t_string_compound_lst *pattern_lst);
int						ft_is_name_character(char c);
int						ft_is_assignement_op(char *str, int *i);
void					ft_expand_tilde(t_string_compound_lst *cmpd,
							char *home_path);
void					ft_expand_compound(t_string_compound_lst *cmpd,
							t_shell_data *data);
t_string_compound_lst	*ft_copy_str_cmpd_flags(t_string_compound_lst *src);
char					*ft_str_cmpd_to_str(t_string_compound_lst *cmpd_lst);
void					ft_str_consume_spaces(t_string_compound_lst *cmpd);
char					*ft_expand_compound_for_var(t_string_compound_lst *cmpd,
							t_shell_data *data);
t_list					*ft_expand_wildcard(t_string_compound_lst *cmpd);
void					ft_clean_cmpd_list(t_list **lst);
int						ft_is_cmpd_always_empty(t_string_compound_lst *cmpd);
void					ft_print_parsed_args(t_list *args);

int						ft_is_cmpd_expanded_somewhere(
							t_string_compound_lst *cmpd);
int						ft_is_cmpd_always_expanded(t_string_compound_lst *cmpd);
int						ft_is_cmpd_always_naked(t_string_compound_lst *cmpd);
int						ft_is_cmpd_always_empty(t_string_compound_lst *cmpd);

void					ft_process_wildcards(t_list **wildcarded_list,
							t_list *post_split_cmpt_list);
void					ft_split_compound_list(t_list **lst_start,
							t_string_compound_lst *cmpd_lst);

#endif
