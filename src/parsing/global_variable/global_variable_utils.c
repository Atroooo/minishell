/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:47:51 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/30 17:15:13 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	skip_simple_quote(int *index, int *nbr_char, char *line)
{
	*index += 1;
	*nbr_char += 1;
	while (line[*index] && line[*index] != '\'')
	{
		*index += 1;
		*nbr_char += 1;
	}
}

int	count_alpha(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && ft_isalnum(line[i]))
		i++;
	return (i);
}

void	skip_gobal_variable(int *index, char *line)
{
	*index += 1;
	if (line[*index] == '?')
		*index += 1;
	else if (line[*index] == '*')
		*index += 1;
	else if (ft_isdigit(line[*index]))
		*index += 1;
	else
		*index += count_alpha(&line[*index]);
}

void	incrementation(int *index, int *nbr_char, char c)
{
	if (c == '\0')
		return ;
	*index += 1;
	*nbr_char += 1;
}
