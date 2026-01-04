/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:11 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/04 23:14:52 by lomartin         ###   ########.fr       */
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

#endif
