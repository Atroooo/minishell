/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:25:13 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/03 13:59:19 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	skip_space(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != '\0' && line[i] == ' ')
			i++;
	return (i);
}

int	count_len(char *line, char del, int *nbr_quote)
{
	int	i;

	i = 1;
	*nbr_quote += 1;
	while (line[i] != '\0' && line[i] != del)
		i++;
	if (line[i] != '\0')
	{
		i += 1;
		*nbr_quote += 1;
	}
	return (i);
}

int	get_size(char *line, int *size)
{
	int		i;
	int		nbr_quote;

	i = 0;
	nbr_quote = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += count_len(&line[i], line[i], &nbr_quote);
		else if ((line[i] == '<' || line[i] == '>') && i > 1)
		{
			break ;
		}
		else
			i += 1;
	}
	*size = i;
	return (i - nbr_quote);
}

static int	set_up_del(int *del, char c)
{
	*del = c;
	return (1);
}

static int	copy_single_char(char *dest, char src, int *y)
{
	dest[*y] = src;
	*y += 1;
	return (1);
}

char	*copy_cmd(int size, char *src, char *dest)
{
	int		i;
	int		del;
	int		y;

	i = 0;
	y = 0;
	del = 0;
	while (i < size)
	{
		if ((src[i] == '\'' || src[i] == '\"') && del == 0)
			i += set_up_del(&del, src[i]);
		else if (del != 0 && src[i] == del)
			i += set_up_del(&del, 0);
		else
			i += copy_single_char(dest, src[i], &y);
	}
	dest[y] = '\0';
	return (dest);
}
