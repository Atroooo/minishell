/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_operator_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:31:27 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 13:59:53 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	simple_operator_error(char *line)
{

	if (line[1] == '\0')
		return (1);
	return (0);
}

static int	double_operator_error(char *line)
{
	if (line[1] == '<')
	{
		if (line[2] == '\0' || line[2] == '<' || line[2] == '>')
			return (1);
	}
	else if (line[1] == '>')
	{
		if (line[2] == '\0' || line[2] == '<' || line[2] == '>')
			return (1);
	}
	return (0);
}

int	input_operator_check(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if (simple_operator_error(&line[i]))
				return (printf("bash: syntax error near unexpected token\n"));
			else if (double_operator_error(&line[i]))
				return (printf("bash: syntax error near unexpected token\n"));
		}
		i++;
	}
	return (0);
}
