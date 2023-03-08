/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:39:37 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/20 17:18:59 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*final_str;
	int		i;
	int		j;

	if (s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	final_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (final_str == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		final_str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		final_str[i] = s2[j];
		i++;
		j++;
	}
	return (final_str[i] = '\0', final_str);
}
