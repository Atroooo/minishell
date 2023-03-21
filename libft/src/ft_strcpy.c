/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:02:01 by neoff             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/17 14:44:20 by atro             ###   ########.fr       */
=======
/*   Updated: 2023/03/18 13:17:36 by neoff            ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strcpy(char *src, char *dest)
{
	int	i;

	i = 0;
	if (src == NULL)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dest == NULL)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
