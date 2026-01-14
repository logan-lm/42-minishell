/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:11 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 07:53:38 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

typedef struct s_command
{
	char					**args;
	int						fdin;
	int						fdout;
	int						fork;
	int						error;
}							t_command;

typedef struct s_hd_data
{
	char					*filename;
	int						temp_w;
	int						temp_r;
	char					*buffer;
	char					*line;
	char					*temp;
	char					*tmppaths[4];
	int						tried_paths;
}							t_hd_data;

typedef struct s_open_data
{
	t_parsing_token			*token;
	t_token_op_data			*op_token;
	t_list					*args_lst;
}							t_open_data;

typedef struct s_parsecmd_data
{
	t_parsing_token			*token;
	t_token_op_data			*op_token;
	t_list					*args_lst;
	t_list					*nodes_cpy;
}							t_parsecmd_data;

typedef struct s_check_wildcards_data
{
	t_list					*curr;
	t_list					*next;
	t_list					*temp;
	char					*arg;
	int						i;
}							t_check_wildcards_data;

typedef struct s_wordtostr_data
{
	char					**splitted;
	char					*temp;
	char					*last_str;
	char					*arg;
	t_list					*last;
	int						i;
	int						no_expand;
}							t_wordtostr_data;

typedef enum e_cmd_type
{
	cmd_builtin,
	cmd_exec,
	cmd_error
}							t_cmd_type;

typedef struct s_runcmd_data
{
	int						pid;
	int						*pipefd;
	int						fd_in;
	int						fd_out;
	void					*cmdpath;
	int						ret;
	t_cmd_type				cmd_type;
}							t_runcmd_data;

typedef struct s_run_pipeline_data
{
	int						has_pipe;
	int						pipeline;
	int						fd_in;
	t_command				*cmd;
	int						ret;
	t_list					opened_heredocs;
}							t_run_pipeline_data;

typedef struct s_next_cmd_data
{
	t_parsing_token			*token;
	t_token_op_data			*op_token;
	t_parsing_token			*token_next;
	t_token_op_data			*op_token_next;
}							t_next_cmd_data;

typedef struct s_assign_vars_data
{
	t_list					*nodes_cpy;
	t_parsing_token			*token;
	t_token_op_data			*op_token;
	t_string_compound_lst	*compounds;
}							t_assign_vars_data;

typedef enum e_parsefd_error_type
{
	error_expand,
	error_open
}							t_parsefd_error_type;

typedef struct s_pase_cmd_args_data
{
	t_list					*args;
	char					*temp;
	t_list					*l;
}							t_parse_cmd_args_data;

// HEREDOCS
int							ft_expand_heredoc(t_token_op_data *op_token,
								t_shell_data *d);
int							ft_parse_heredocs(t_list *nodes, t_shell_data *d);
int							ft_heredoc_eof_err(t_shell_data *data,
								char *limiter, int fd_r);
int							ft_heredoc_handler(void);
char						*ft_read_expand_fd(int fd);
int							ft_open_heredoc(t_token_op_data *op_token,
								t_shell_data *d, int oldfd);

// RUN
int							ft_run_cmd(t_run_pipeline_data *rp_d,
								t_shell_data *data, void *next);
int							ft_run_builtin(int (*builtin)(char **a,
									t_shell_data *d, int in, int out),
								t_run_pipeline_data *rp_d, t_runcmd_data *r_d,
								t_shell_data *data);
void						ft_try_get_cmd(t_runcmd_data *r_d,
								t_run_pipeline_data *rp_d, t_shell_data *data);
int							ft_close_onerror(t_run_pipeline_data *rp_d,
								t_runcmd_data *r_d, void *next);
void						ft_run_init_fds(t_runcmd_data *r_d,
								t_run_pipeline_data *rp_d, void *next);

int							ft_parse_fd(t_list *nodes, t_shell_data *d,
								t_run_pipeline_data *data);
void						ft_consume_fdin(int fdin);
void						ft_set_tmp_paths(t_hd_data *hd_data,
								t_shell_data *data);
int							ft_try_open_tmpfile(t_hd_data *hd_data);
int							ft_has_pipe(t_list *nodes);
t_list						*ft_next_cmd(t_list *nodes);
int							ft_and(t_command_node *command_tree,
								t_shell_data *data);
int							ft_or(t_command_node *command_tree,
								t_shell_data *data);
int							ft_subshell(char **args, t_shell_data *data,
								int fdin, int fdout);
int							ft_parsefd_err(char *filename, char *progname,
								t_run_pipeline_data *runp_d,
								t_parsefd_error_type type);
int							ft_is_limiter(char *str, char *limiter);
int							ft_str_hasspace(char *str);
int							ft_ispath(char *str);
char						*ft_get_cmdpath(char *cmd, t_list *envp, int *ret,
								char *progname);
char						*ft_getvarname(char *str);
t_list						*ft_parse_cmd(t_list **nodes, t_shell_data *d);
t_list						*ft_get_sorted_dircontent(char *path, int dir,
								int include_hidden);
t_list						*ft_check_wildcards(t_list *args,
								t_shell_data *data);
t_list						*ft_chech_matchs(t_list *args, t_shell_data *data);
int							ft_is_only_varset(t_list *commands);
void						ft_sig_hd_handler(int sig);
int							ft_o_hdoc(char *limiter, int oldfd,
								t_shell_data *data);
char						*ft_copy_nonspecial(char **word, char *src);
char						*ft_expand_word(char *word, t_shell_data *data,
								t_string_compound_lst *cmpd_node);
void						ft_expand_compound(t_string_compound_lst *cmpd,
								t_shell_data *data);
void						ft_save_src(t_list **src);

#endif
