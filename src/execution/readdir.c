/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:33:13 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/14 08:33:19 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_get_sorted_dircontent(char *path, int dir, int include_hidden)
{
	DIR				*dirp;
	struct dirent	*read;
	t_list			*filenames;

	if (*path)
		dirp = opendir(path);
	else
		dirp = opendir(".");
	if (!dirp)
		return (NULL);
	filenames = NULL;
	read = readdir(dirp);
	while (read)
	{
		if (((include_hidden && ft_strcmp("..", read->d_name) && ft_strcmp(".",
						read->d_name)) || *(read->d_name) != '.') && (!dir
				|| read->d_type == DT_DIR || read->d_type == DT_LNK))
			ft_lstadd_front(&filenames, ft_lstnew_gc_id(ft_strjoin_gc_id(path,
						read->d_name, malloc_id_exec), malloc_id_exec));
		read = readdir(dirp);
	}
	closedir(dirp);
	ft_lstsort(&filenames, ft_strcmp);
	return (filenames);
}
