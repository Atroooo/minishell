/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 07:58:46 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/11 10:24:30 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	get_number_split(char const *s, char c, int *y)
{
	int		i;
	int		size;
	int		start;

	if (s == NULL)
		return (0);
	*y = 0;
	i = 0;
	size = 1;
	start = 0;
	while (s[i])
	{	
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start < i)
			size++;
	}
	return (size);
}

static int	get_size_split(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	*malloc_error(char **result, int result_index)
{
	int	i;

	i = 0;
	while (i < result_index)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static int	check_ifsame_char(const char *s, char c, int i, int sw)
{
	if (sw == 0)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		return (i);
	}
	else
	{
		while (s[i] == c && s[i])
		{
			i++;
		}
		return (i);
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		y;
	int		j;
	char	**result;

	i = 0;
	result = malloc((get_number_split(s, c, &y)) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	if ((size_t)check_ifsame_char(s, c, 0, 1) != ft_strlen(s))
	{
		while (s[i] != '\0')
		{
			i = check_ifsame_char(s, c, i, 0);
			j = 0;
			result[y] = malloc((get_size_split(&s[i], c) + 1) * sizeof(char));
			if (result[y] == NULL)
				return (malloc_error(result, c));
			while (s[i] != '\0' && s[i] != c)
				result[y][j++] = s[i++];
			result[y++][j] = '\0';
			i = check_ifsame_char(s, c, i, 0);
		}
	}
	return (result[y] = 0, result);
}
