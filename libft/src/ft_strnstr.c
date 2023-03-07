/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:34:31 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:53:16 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	length;

	if (str == NULL && len == 0)
		return (NULL);
	length = ft_strlen(to_find);
	i = 0;
	k = 0;
	while (str[i] && k < length && i < len)
	{
		k = 0;
		while (str[i + k] == to_find[k] && to_find[k] && k + i < len)
		{
			k++;
		}
		i++;
	}
	if (!(to_find[0]))
		return (((char *)str));
	if (k == length)
		return (&((char *)str)[i - 1]);
	return (0);
}
