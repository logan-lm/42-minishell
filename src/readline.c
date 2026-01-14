/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:29:50 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 09:00:47 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		if (!ft_gethd())
			write(1, "\n", 1);
		if (ft_getpid() == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault : (core dumped)\n", STDERR_FILENO);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (sig == SIGKILL)
		ft_putstr_fd("Killed\n", STDERR_FILENO);
	else if (sig == SIGTERM)
		ft_putstr_fd("Terminated\n", STDERR_FILENO);
}

void	ft_split_prompt(char *prompt, t_shell_data *d)
{
	char			**prompt_childs;
	int				i;
	t_list			*token_lst;
	t_command_node	*command_tree;

	prompt_childs = ft_split_gc(prompt, '\n');
	i = -1;
	while (prompt_childs[++i])
	{
		if (d->interactive)
			add_history(prompt_childs[i]);
		token_lst = ft_get_tokens(prompt_childs[i]);
		if (token_lst)
			command_tree = ft_build_ast(token_lst);
		else
			command_tree = NULL;
		if (BUILD_DEBUG)
			ft_print_ast_visual(command_tree, "");
		ft_dictadd(&d->vars, "?", ft_itoa_gc_id(ft_exec(command_tree, d),
				malloc_id_exec));
		ft_clear_gc_id(malloc_id_token);
		ft_clear_gc_id(malloc_id_ast);
		ft_clear_gc_id(malloc_id_exec);
	}
	ft_free_strs(prompt_childs);
}

char	*ft_read_cmd(void)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*dest;
	char	*temp;
	ssize_t	read_bytes;

	dest = ft_strdup("");
	read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	buffer[read_bytes] = '\0';
	while (read_bytes)
	{
		temp = dest;
		dest = ft_strjoin(dest, buffer);
		free(temp);
		read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		buffer[read_bytes] = '\0';
	}
	close(STDIN_FILENO);
	return (dest);
}

void	ft_readline(t_shell_data *d)
{
	char	*prompt;

	g_sig = 0;
	if (d->interactive)
		prompt = readline(ft_get_prompt());
	else
		prompt = get_next_line_no_nl(STDIN_FILENO);
	if (BUILD_DEBUG && prompt)
		ft_gc_debug(prompt);
	if (g_sig == SIGINT)
		ft_dictadd(&d->vars, "?", "130");
	ft_sethd(0);
	g_sig = 0;
	if (prompt == NULL)
	{
		if (d->interactive)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_exit(ft_atoi(ft_getvar(d->vars, d->envp, d->argv, "?")));
	}
	if (*prompt == '\0')
		return ;
	ft_split_prompt(prompt, d);
	free(prompt);
}
