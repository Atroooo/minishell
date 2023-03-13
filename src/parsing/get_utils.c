/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:25:13 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/13 07:30:09 by vgonnot          ###   ########.fr       */
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

int	count_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		i++;
	}
	return (i);
}
