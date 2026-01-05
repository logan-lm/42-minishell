/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:11 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/05 15:21:30 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

typedef struct s_command
{
	char			**args;
	int				fdin;
	int				fdout;
}					t_command;

typedef struct s_hd_data
{
	char			*filename;
	int				temp_w;
	int				temp_r;
	char			*buffer;
	char			*line;
}					t_hd_data;

typedef struct s_open_data
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;
	t_list			*args_lst;
	int				fd;
}					t_open_data;

typedef struct s_parsecmd_data
{
	t_parsing_token	*token;
	t_token_op_data	*op_token;
	t_list			*args_lst;
	t_list			*nodes_cpy;
}					t_parsecmd_data;

typedef struct s_check_wildcards_data
{
	t_list			*curr;
	t_list			*next;
	t_list			*temp;
	char			*arg;
	int				i;
}					t_check_wildcards_data;

typedef struct s_wordtostr_data
{
	char			**splitted;
	char			*temp;
	char			*arg;
	t_list			*last;
	int				i;
}					t_wordtostr_data;

typedef struct s_runcmd_data
{
	int				pid;
	int				pipefd[2];
	void			*cmdpath;
	int				ret;
}					t_runcmd_data;

int					ft_parse_fdin(t_list *nodes, t_shell_data *d);
int					ft_parse_fdout(t_list *nodes, t_shell_data *d);
int					ft_has_pipe(t_list *nodes);
t_list				*ft_next_cmd(t_list *nodes);
int					ft_and(t_command_node *command_tree, t_shell_data *data);
int					ft_or(t_command_node *command_tree, t_shell_data *data);
int					ft_subshell(char **args, t_shell_data *data, int fdout);
int					ft_open_err(char *filename, char *progname);
int					ft_exp_err(char *filename, char *progname);
int					ft_heredoc_eof_err(t_shell_data *data, char *limiter,
						int fd_w, int fd_r);
int					ft_is_limiter(char *str, char *limiter);
int					ft_str_hasspace(char *str);
t_list				*ft_separate_cmdname(char *arg);
int					ft_ispath(char *str);
char				*ft_get_cmdpath(char *cmd, t_list *envp);
char				*ft_getvarname(char *str);
t_list				*ft_parse_cmd(t_list **nodes, t_shell_data *d);
t_list				*ft_get_sorted_dircontent(char *path, int dir);
t_list				*ft_check_wildcards(t_list *args, t_shell_data *data);
int					ft_run_cmd(int fdin, t_command *cmd, t_shell_data *data,
						void *next);
int					ft_run_builtin(int (*builtin)(char **a, t_shell_data *d,
							int in, int out), t_command *cmd,
						t_shell_data *data, void *next, int fdin);
int					ft_is_only_varset(t_list *commands);

#endif
