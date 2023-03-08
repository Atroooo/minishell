/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 08:02:48 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:53:16 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*result;

	result = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			result = &((char *)s)[i];
		}
		i++;
	}
	if (c == 0)
		return (&((char *)s)[i]);
	return (result);
}
