/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:25:13 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/08 15:51:38 by lcompieg         ###   ########.fr       */
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
