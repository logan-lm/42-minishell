/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:31:52 by lomartin          #+#    #+#             */
/*   Updated: 2025/12/27 09:49:05 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

char	**parse_cmd(char **args)
{
	int			i;
	int			j;
	t_pipe		pipe;

	i = 1 + data->here_doc;
	while (++i < ac - 1)
	{
		cmd = malloc(sizeof(t_cmd_elem));
		if (!cmd)
			printerr_alloc();
		cmd->args = ft_split(av[i], ' ');
		if (!cmd->args)
			printerr_alloc();
		cmd->path = get_cmd_path(cmd->args[0], envp);
		if (!*cmd->path)
		{
			j = -1;
			while (cmd->args[++j])
				free(cmd->args[j]);
			free(cmd->args);
			cmd->args = ft_split("[invalid]", ' ');
		}
		ft_lstadd_back(&(data->cmds), ft_lstnew((void *)cmd));
		data->cmd_count++;
	}
}
