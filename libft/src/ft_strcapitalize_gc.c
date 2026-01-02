/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize_gc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomartin <lomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 20:27:56 by lomartin          #+#    #+#             */
/*   Updated: 2026/01/02 20:33:00 by lomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_to_lower_gc(char *str)
{
	char	*dest;
	size_t	i;

	i = -1;
	if (!str)
		return (NULL);
	dest = ft_malloc(ft_strlen(str) + 1);
	while (str[++i])
		dest[i] = ft_tolower(str[i]);
	return (dest);
}

char	*ft_str_to_upper_gc(char *str)
{
	char	*dest;
	size_t	i;

	i = -1;
	if (!str)
		return (NULL);
	dest = ft_malloc(ft_strlen(str) + 1);
	while (str[++i])
		dest[i] = ft_toupper(str[i]);
	return (dest);
}
