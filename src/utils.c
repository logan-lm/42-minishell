/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 18:31:12 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/14 17:47:02 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_path(char *path, t_shell_data *s_data)
{
	char 	*parsed_path;
	char	*pwd;

	if (!path)
		return (path);
	if (*path == '~')
	{
		parsed_path = ft_strjoin_gc(ft_dictmap(s_data->envp, "HOME"), path + 1);
		ft_free(path);
	}
	else if (*path != '/')
	{
		pwd = ft_dictmap(s_data->envp, "PWD");
		if (pwd[ft_strlen(pwd) - 1 == '/'])
			parsed_path = ft_strjoin_gc(pwd, path);
		else
			parsed_path = ft_strjoin_mult_gc(3, pwd, "/", path);
		ft_free(path);
	}
	else
		parsed_path = path;
	return (parsed_path);
}
