/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:00:43 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/20 16:32:09 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

size_t	ft_strlen_c(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin_c(char *s1, char *s2, int len, int *size_dest)
{
	char	*final_str;
	int		i;
	int		j;

	if (s2 == NULL)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	final_str = malloc(sizeof(char) * (ft_strlen_c(s1) + ft_strlen_c(s2)) + 1);
	if (final_str == NULL)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		final_str[i] = s1[i];
		i++;
	}
	if (s1 != NULL)
		free(s1);
	while (s2[j] && j < len)
	{
		final_str[i] = s2[j];
		i++;
		j++;
	}
	return (final_str[i] = '\0', *size_dest = i, final_str);
}

void	*ft_memcpy_c(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (src == NULL && dst == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

char	*delete_substring(char *destination, char *source)
{
	int		i;

	i = 0;
	while (source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}
	ft_memset_c(&destination[i], 0, BUFFER_SIZE - i);
	return (destination);
}

void	ft_memset_c(char *b, int c, size_t len)
{
	size_t			i;
	char			*str;

	str = b;
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	b = str;
}
