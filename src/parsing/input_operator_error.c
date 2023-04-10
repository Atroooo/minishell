/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_operator_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:31:27 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/31 22:07:04 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	simple_operator_error(char *line)
{

	if (line[1] == '\0')
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		return (1);
	}
	return (0);
}

static int	check_if_operator(char *line, char operator)
{
	int	i;

	i = 0;
	i += skip_space(&line[i + 1]) + 1;
	if (operator == '>' && line[i] == '<')
	{
		i += skip_space(&line[i +1]) + 1;
		if (line[i] == '\0')
			return (printf("bash: syntax error near unexpected token `%c'\n", operator));
	}
	if (line[i] == operator)
	{
		i += skip_space(&line[i + 1]) + 1;
		if (line[i] == '\0' && line[i])
			return (printf("bash: syntax error near unexpected token 'newline'\n"));
		if (line[i] == '<' || line[i] == '>')
		{
			i += skip_space(&line[i + 1]) + 1;
			if (line[i] == '<' || line[i] == '>')
				return (printf("bash: syntax error near unexpected token `%c%c'\n", operator, operator));
			return (printf("bash: syntax error near unexpected token `%c'\n", operator));
		}
	}
	return (0);
}

static int	double_operator_error(char *line)
{
	if (check_if_operator(line, '>'))
		return (1);
	else if (check_if_operator(line, '<'))
		return (1);
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
				return (1);
			else if (double_operator_error(&line[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
