/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:39:16 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/11 15:04:51 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_str_isdigit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*(str)++))
			return (0);
	}
	return (1);
}

int	ft_shell_exit(char **args, t_shell_data *data, int fdin, int fdout)
{
	char	*err;

	if (fdin != STDIN_FILENO)
		close(fdin);
	args++;
	while (wait(NULL) > 0)
		;
	if (data->interactive)
		ft_putstr_fd("exit\n", fdout);
	if (fdout != STDOUT_FILENO)
		close(fdout);
	if (*args)
	{
		if ((**args != '+' && **args != '-' && !ft_isdigit(**args))
			|| !ft_str_isdigit(*args + 1))
		{
			err = ft_strjoin_mult_gc_id(malloc_id_exec, 3, "exit: ", *args,
					": numeric argument required");
			ft_print_error(err, data->progname);
			ft_exit(2);
		}
		if (*(args + 1))
			return (ft_print_error("exit: too many arguments", data->progname));
		data->exit_status = (unsigned char)ft_atoi(*args);
	}
	return (ft_exit(data->exit_status), EXIT_SUCCESS);
}
