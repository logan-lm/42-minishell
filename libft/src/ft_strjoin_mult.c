/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_mult.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberne <pberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:18:51 by pberne            #+#    #+#             */
/*   Updated: 2025/12/08 19:24:01 by pberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_list_gc(t_list *list, size_t size)
{
	char	*tempstr;
	char	*temp;
	char	*str;

	str = ft_malloc(size + 1);
	tempstr = str;
	str[size] = '\0';
	while (list)
	{
		temp = (char *)(list->content);
		while (*temp)
		{
			*tempstr = *temp;
			tempstr++;
			temp++;
		}
		list = list->next;
	}
	return (str);
}

char	*ft_strjoin_mult_gc(int nb, ...)
{
	va_list	ap;
	t_list	*list;
	char	*temp;
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	list = 0;
	va_start(ap, nb);
	while (i < nb)
	{
		temp = va_arg(ap, char *);
		size += ft_strlen(temp);
		ft_lstadd_back(&list, ft_lstnew_gc(temp));
		i++;
	}
	va_end(ap);
	temp = ft_strjoin_list_gc(list, size);
	ft_lstclear_gc(&list, 0);
	return (temp);
}

char	*ft_strjoin_list(t_list *list, size_t size)
{
	char	*tempstr;
	char	*temp;
	char	*str;

	str = malloc(size + 1);
	if (!str)
		return (0);
	tempstr = str;
	str[size] = '\0';
	while (list)
	{
		temp = (char *)(list->content);
		while (*temp)
		{
			*tempstr = *temp;
			tempstr++;
			temp++;
		}
		list = list->next;
	}
	return (str);
}

char	*ft_strjoin_mult(int nb, ...)
{
	va_list	ap;
	t_list	*list;
	char	*temp;
	size_t	size;
	int		i;

	i = 0;
	size = 0;
	list = 0;
	va_start(ap, nb);
	while (i < nb)
	{
		temp = va_arg(ap, char *);
		size += ft_strlen(temp);
		ft_lstadd_back(&list, ft_lstnew(temp));
		i++;
	}
	va_end(ap);
	temp = ft_strjoin_list(list, size);
	ft_lstclear(&list, 0);
	return (temp);
}
