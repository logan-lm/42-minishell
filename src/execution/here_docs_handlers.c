/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:34:55 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 16:35:12 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

int	ft_heredoc_handler(void)
{
	if (g_sig == 130)
		rl_done = 1;
	return (0);
}

void	ft_sig_hd_handler(int sig)
{
	(void)sig;
	g_sig = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
