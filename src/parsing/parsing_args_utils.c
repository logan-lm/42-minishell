/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 12:17:19 by pberne            #+#    #+#             */
/*   Updated: 2026/01/14 07:18:13 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

/// @brief Expands ~ or -, then variables, then split, then clean,
/// then process wildcards
/// and return a list of chars defining the arguments
t_list	*ft_parse_cmd_args(t_string_compound_lst *lst, t_shell_data *d)
{
	t_string_compound_lst	*iterator;
	t_list					*post_split_cmpt_list;
	t_list					*wildcarded_list;

	post_split_cmpt_list = NULL;
	wildcarded_list = NULL;
	iterator = lst;
	while (iterator)
	{
		ft_expand_tilde(iterator, ft_getvar(d->vars, d->envp, d->argv, "HOME"));
		iterator = iterator->next;
	}
	iterator = lst;
	while (iterator)
	{
		ft_expand_compound(iterator, d);
		iterator = iterator->next;
	}
	ft_split_compound_list(&post_split_cmpt_list, lst);
	ft_clean_cmpd_list(&post_split_cmpt_list);
	ft_process_wildcards(&wildcarded_list, post_split_cmpt_list);
	return (wildcarded_list);
}
