/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:33:13 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/02 20:19:49 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_sorted_dircontent(char *path, int dir)
{
	DIR				*dirp;
	struct dirent	*read;
	t_list			*filenames;
	char			**fn;

	if (*path)
		dirp = opendir(path);
	else
		dirp = opendir(".");
	filenames = NULL;
	read = readdir(dirp);
	while (read)
	{
		if (*(read->d_name) != '.' && (!dir || read->d_type == DT_DIR))
			ft_lstadd_front(&filenames, ft_lstnew(ft_strjoin_gc(path,
						read->d_name)));
		read = readdir(dirp);
	}
	closedir(dirp);
	ft_lstsort(&filenames, ft_strcmp);
	fn = ft_lsttostrs(filenames);
	ft_lstclear(&filenames, NULL);
	return (fn);
}
