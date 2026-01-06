/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:14:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/06 13:10:06 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_heredoc_handler(void)
{
	if (g_sig == SIGINT)
		rl_done = 1;
	return (0);
}

void	ft_sig_hd_handler(int sig)
{
	g_sig = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char	*ft_o_hdoc_while(char *limiter, t_hd_data *hd_data, t_shell_data *data)
{
	while (!ft_is_limiter(hd_data->line, limiter) && g_sig != SIGINT)
	{
		ft_free(hd_data->line);
		hd_data->buffer = readline("> ");
		hd_data->line = ft_strjoin_gc_id(hd_data->buffer, "\n", malloc_id_exec);
		free(hd_data->buffer);
		if (!hd_data->buffer)
			return (ft_heredoc_eof_err(data, limiter, hd_data->temp_w,
					hd_data->filename));
		if (ft_is_limiter(hd_data->line, limiter))
			break ;
		write(hd_data->temp_w, hd_data->line, ft_strlen(hd_data->line));
	}
	return (NULL);
}

char	*ft_o_hdoc(char *limiter, t_shell_data *data)
{
	t_hd_data	hd_data;
	char		*ret;

	ft_bzero(&hd_data, sizeof(hd_data));
	hd_data.temp = ft_ltoa_gc((long)limiter);
	hd_data.filename = ft_strjoin_gc_id("/tmp/heredoc_", hd_data.temp,
			malloc_id_exec);
	ft_free(hd_data.temp);
	hd_data.temp_w = open(hd_data.filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (hd_data.temp_w == -1)
		return (ft_strdup_gc_id("FAILED_OPEN", malloc_id_exec));
	ft_lstadd_front(&data->opened_hd, ft_lstnew_gc_id(hd_data.filename,
			malloc_id_exec));
	ft_setfd(hd_data.temp_w);
	rl_event_hook = ft_heredoc_handler;
	ret = ft_o_hdoc_while(limiter, &hd_data, data);
	if (ret)
		return (ret);
	close(hd_data.temp_w);
	ft_free(hd_data.line);
	return (hd_data.filename);
}

void	ft_unlink_hds(t_shell_data *data)
{
	t_list	*hds;
	int		fd;

	fd = ft_getfd();
	if (fd != STDIN_FILENO)
		close(fd);
	hds = data->opened_hd;
	while (hds)
	{
		unlink(hds->content);
		hds = hds->next;
	}
	ft_lstclear_gc(&data->opened_hd, ft_free);
}
