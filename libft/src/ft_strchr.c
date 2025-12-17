/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:36:40 by pberne            #+#    #+#             */
/*   Updated: 2025/12/17 14:26:42 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*out;
	char	cc;

	cc = (char)c;
	i = 0;
	out = 0;
	while (str[i])
	{
		if (str[i] == cc)
			break ;
		i++;
	}
	if (str[i] == cc)
		out = (char *)str + i;
	return (out);
}
