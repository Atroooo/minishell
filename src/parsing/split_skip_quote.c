/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_skip_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 07:58:46 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/10 17:03:06 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	skip_in_between(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
	if (str[i] == c)
		i += 1;
	return (i);
}

static int	get_number_split(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_in_between(&str[i], str[i]);
		else if (str[i] == '|')
		{
			while (str[i] == '|')
				i++;
			result += 1;
		}
		else if (str[i] != '\0')
			i++;
	}
	return (result);
}

static int	get_len_split(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '|' )
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i += skip_in_between(&str[i], str[i]);
		}
		else if (str[i] != '\0')
			i ++;
	}
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

static int	split_execution(char *str, char **result)
{
	int	len;

	len = get_len_split(str);
	*result = malloc((len + 1) * sizeof(char));
	if (*result == NULL)
		return (INT_MIN);
	ft_strlcpy(*result, str, len + 1);
	return (len);
}

char	**split_skip_quote(char *str)
{
	char	**result;
	int		i;
	int		y;

	i = 0;
	y = 0;
	result = malloc((get_number_split(str) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		i += skip_char(&str[i], '|');
		if (str[i] != '\0')
			i += split_execution(&str[i], &result[y]);
		if (i < 0)
			return (malloc_error(result, y));
		if (str[i] != '\0')
			i += 1;
		y++;
	}
	result[y] = NULL;
	return (result);
}
