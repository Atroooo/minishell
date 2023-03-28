/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 09:07:46 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/28 09:12:46 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t			i;
	int				lenght;

	lenght = size;
	if (size == 0)
		return (lenght);
	i = 0;
	while (src[i] && size > 1)
	{
		dest[i] = src[i];
		i++;
		size--;
	}
	dest[i] = '\0';
	return (lenght);
}
