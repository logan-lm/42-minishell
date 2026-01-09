/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:36:14 by pberne            #+#    #+#             */
/*   Updated: 2026/01/09 11:36:14 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rgb	ft_get_color(int id)
{
	if (id == 0)
		return ((t_rgb){255, 239, 100});
	if (id == 1)
		return ((t_rgb){255, 196, 0});
	if (id == 2)
		return ((t_rgb){255, 161, 81});
	if (id == 3)
		return ((t_rgb){255, 122, 101});
	if (id == 4)
		return ((t_rgb){255, 104, 239});
	if (id == 5)
		return ((t_rgb){210, 120, 255});
	if (id == 6)
		return ((t_rgb){154, 160, 255});
	if (id == 7)
		return ((t_rgb){147, 237, 255});
	if (id == 8)
		return ((t_rgb){146, 255, 191});
	else
		return ((t_rgb){180, 255, 70});
}

char	*ft_get_char_colored(t_rgb color, char *c)
{
	char	*str;

	str = ft_strjoin_mult_gc_id(0, 9, "\001\033[38;2;", ft_itoa_gc(color.r),
			";", ft_itoa_gc(color.g), ";", ft_itoa_gc(color.b), "m\002",
			c, "\001\033[0m\002");
	return (str);
}

char	*ft_get_string_colored(int start_id)
{
	char	*str;

	str = ft_strjoin_mult_gc_id(0, 10,
			ft_get_char_colored(ft_get_color((start_id) % 10), "M"),
			ft_get_char_colored(ft_get_color((start_id + 1) % 10), "i"),
			ft_get_char_colored(ft_get_color((start_id + 2) % 10), "n"),
			ft_get_char_colored(ft_get_color((start_id + 3) % 10), "i"),
			ft_get_char_colored(ft_get_color((start_id + 4) % 10), "s"),
			ft_get_char_colored(ft_get_color((start_id + 5) % 10), "h"),
			ft_get_char_colored(ft_get_color((start_id + 6) % 10), "e"),
			ft_get_char_colored(ft_get_color((start_id + 7) % 10), "l"),
			ft_get_char_colored(ft_get_color((start_id + 8) % 10), "l"),
			ft_get_char_colored(ft_get_color((start_id + 9) % 10), ">"));
	return (str);
}

char	**ft_setup_prompts(void)
{
	char	**p;
	int		i;

	p = ft_malloc(sizeof(char *) * 10);
	i = 0;
	while (i < 10)
	{
		p[i] = ft_get_string_colored(i);
		i++;
	}
	return (p);
}

char	*ft_get_prompt(void)
{
	static int	id = -1;
	static char	**prompts;

	if (id == -1)
		prompts = ft_setup_prompts();
	id++;
	id = id % 10;
	return (prompts[id]);
}
