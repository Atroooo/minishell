/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:38:45 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:53:16 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	nbr_charset_beginning(char const *s1, char const *set)
{
	int	i;
	int	check;
	int	y;

	check = 1;
	i = 0;
	while (check == 1 && s1[i])
	{
		y = 0;
		check = 0;
		while (set[y])
		{
			if (set[y] == s1[i])
				check = 1;
			y++;
		}
		i++;
	}
	i -= 1;
	return (i);
}

static int	nbr_charset_end(char const *s1, char const *set, int len)
{
	int	check;
	int	y;

	check = 1;
	len -= 1;
	while (check == 1 && len >= 0)
	{
		y = 0;
		check = 0;
		while (set[y])
		{
			if (set[y] == s1[len])
				check = 1;
			y++;
		}
		len--;
	}
	len += 1;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	char	*final_str;
	int		j;

	if (s1 == NULL)
		return (NULL);
	j = 0;
	begin = nbr_charset_beginning(s1, set);
	end = nbr_charset_end(s1, set, ft_strlen(s1));
	if (end >= begin)
		final_str = malloc(sizeof(char) * (end - begin + 2));
	else
		final_str = malloc(1);
	if (final_str == NULL)
		return (NULL);
	while (begin <= end)
	{
		final_str[j] = s1[begin];
		begin ++;
		j++;
	}
	final_str[j] = 0;
	return (final_str);
}
