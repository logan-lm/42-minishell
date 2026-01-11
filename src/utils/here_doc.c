/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:44:14 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 16:40:48 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

static int	ft_hd(int flag, int hd)
{
	static int	s_hd = 0;

	if (flag == 0)
		return (s_hd);
	if (flag == 1)
		s_hd = hd;
	return (0);
}

int	ft_gethd(void)
{
	return (ft_hd(0, 0));
}

void	ft_sethd(int hd)
{
	ft_hd(1, hd);
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
