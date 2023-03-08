/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_operator_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:31:27 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/07 15:13:12 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	simple_operator_error(char *cmd_line)
{

	if (cmd_line[1] == '\0')
		return (1);
	return (0);
}

int	double_operator_error(char *cmd_line)
{
	if (cmd_line[1] == '<')
	{
		if (cmd_line[2] == '\0' || cmd_line[2] == '<' || cmd_line[2] == '>')
			return (1);
	}
	else if (cmd_line[1] == '>')
	{
		if (cmd_line[2] == '\0' || cmd_line[2] == '<' || cmd_line[2] == '>')
			return (1);
	}
	return (0);
}

int	input_operator_check(char *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i] != '\0')
	{
		if (cmd_line[i] == '<' || cmd_line[i] == '>')
		{
			if (simple_operator_error(&cmd_line[i]))
				return (1);
			else if (double_operator_error(&cmd_line[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
