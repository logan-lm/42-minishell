/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:36:11 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/30 22:34:57 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

typedef struct s_command
{
	char	**args;
	int		fdin;
	int		fdout;
}			t_command;

int			ft_parse_fdin(t_list *nodes, t_shell_data *d);
int			ft_parse_fdout(t_list *nodes, t_shell_data *d);
int			ft_has_pipe(t_list *nodes);
t_list		*ft_next_cmd(t_list *nodes);
int			ft_and(t_command_node *command_tree, t_shell_data *data);
int			ft_or(t_command_node *command_tree, t_shell_data *data);
int			ft_subshell(char **args, t_shell_data *data, int fdout);
int			ft_open_err(int fd, char *filename, char *progname);
int			ft_exp_err(int fd, char *filename, char *progname);
int			ft_heredoc_eof_err(t_shell_data *data, char *limiter, int fd_w,
				int fd_r);
int			ft_is_limiter(char *str, char *limiter);
int			ft_str_hasspace(char *str);

#endif
