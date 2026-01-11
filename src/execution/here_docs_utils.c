/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:14:34 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 09:53:47 by lomartin         ###   ########.fr       */
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
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	ft_try_open_tmpfile(t_hd_data *hd_data)
{
	if (!hd_data->tmppaths[hd_data->tried_paths])
		return (1);
	hd_data->filename = ft_strjoin_gc_id(
			hd_data->tmppaths[hd_data->tried_paths],
			hd_data->temp, malloc_id_exec);
	hd_data->temp_w = open(hd_data->filename, O_WRONLY | O_CREAT | O_TRUNC,
			0600);
	hd_data->temp_r = open(hd_data->filename, O_RDONLY);
	unlink(hd_data->filename);
	if (hd_data->temp_w < 0 || hd_data->temp_r < 0)
	{
		if (hd_data->temp_w > 2)
			close(hd_data->temp_w);
		if (hd_data->temp_r > 2)
			close(hd_data->temp_r);
		hd_data->tried_paths++;
		return (ft_try_open_tmpfile(hd_data));
	}
	return (0);
}

int	ft_o_hdoc_while(char *limiter, t_hd_data *hd_data)
{
	while (!ft_is_limiter(hd_data->line, limiter) && g_sig != SIGINT)
	{
		ft_free(hd_data->line);
		hd_data->buffer = readline("> ");
		// hd_data->buffer = get_next_line(0);
		if (!hd_data->buffer)
		{
			ft_sethd(1);
			close(hd_data->temp_w);
			return (1);
		}
		hd_data->line = ft_strjoin_gc_id(hd_data->buffer, "\n", malloc_id_exec);
		free(hd_data->buffer);
		if (ft_is_limiter(hd_data->line, limiter))
			break ;
		write(hd_data->temp_w, hd_data->line, ft_strlen(hd_data->line));
	}
	return (0);
}

void	ft_set_tmp_paths(t_hd_data *hd_data, t_shell_data *data)
{
	int		i;
	char	*path;

	i = 0;
	path = ft_getenv(data->envp, "TMPDIR");
	if (*path)
	{
		hd_data->tmppaths[i++] = ft_strjoin_gc_id(path, "/heredoc_",
				malloc_id_exec);
		ft_free(path);
	}
	hd_data->tmppaths[i++] = ft_strdup_gc_id("/tmp/heredoc_", malloc_id_exec);
	hd_data->tmppaths[i++] = ft_strdup_gc_id("/var/tmp/heredoc_",
			malloc_id_exec);
}

int	ft_o_hdoc(char *limiter, int oldfd, t_shell_data *data)
{
	t_hd_data	hd_data;
	int			ret;

	if (oldfd > 2)
		close(oldfd);
	ft_bzero(&hd_data, sizeof(hd_data));
	hd_data.temp = ft_ltoa_gc((long)limiter);
	ft_set_tmp_paths(&hd_data, data);
	if (ft_try_open_tmpfile(&hd_data))
		return (-1);
	ft_free(hd_data.temp);
	ft_lstadd_front(&data->opened_hd, ft_lstnew_gc_id(hd_data.filename,
			malloc_id_exec));
	ft_setfd(hd_data.temp_w);
	rl_event_hook = ft_heredoc_handler;
	ret = ft_o_hdoc_while(limiter, &hd_data);
	rl_event_hook = NULL;
	close(hd_data.temp_w);
	ft_free(hd_data.filename);
	if (ret)
		return (ft_heredoc_eof_err(data, limiter, hd_data.temp_r));
	ft_free(hd_data.line);
	return (hd_data.temp_r);
}
