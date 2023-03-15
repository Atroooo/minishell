/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:25:13 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/15 09:00:56 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
