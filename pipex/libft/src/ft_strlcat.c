/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:33:42 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:53:16 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	int				i;
	unsigned int	dest_size;
	int				j;

	if (dest == NULL && size == 0)
		return (0);
	dest_size = ft_strlen(dest);
	i = 0;
	if (size < dest_size)
		return (size + ft_strlen(src));
	while (dest[i] != '\0' && size > 0)
	{
		i++;
		size--;
	}
	j = 0;
	while (src[j] != '\0' && size > 1)
	{
		dest[i + j] = src[j];
		size--;
		j++;
	}
	if (size > 0)
		dest[i + j] = '\0';
	return (dest_size + ft_strlen(src));
}
