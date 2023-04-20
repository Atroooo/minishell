/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_operator_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:31:27 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/20 15:38:41 by vgonnot          ###   ########.fr       */
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

static int	first_case_error(char *line, int *i)
{
	char	operator;

	operator = line[*i];
	*i += skip_space(&line[*i +1]) + 1;
	if (line[*i] == '\0')
	{
		printf("bash: syntax error near unexpected token `%c'\n", operator);
		return (1);
	}
	return (0);
}

static int	second_case_error(char *line, int *i, char operator)
{
	*i += skip_space(&line[*i + 1]) + 1;
	if (line[*i] == '\0' && line[*i])
		return (printf("bash: syntax error near unexpected token 'newline'\n"));
	if (line[*i] == '<' || line[*i] == '>')
	{
		*i += skip_space(&line[*i + 1]) + 1;
		if (line[*i] == '<' || line[*i] == '>')
			printf("bash: syntax error near unexpected token `%c%c'\n", operator, operator);
		else
			printf("bash: syntax error near unexpected token `%c'\n", operator);
		return (1);
	}
	return (0);
}

static int	check_if_operator(char *line, char operator, int original_index)
{
	int	i;

	i = 0;
	i += skip_space(&line[i + 1]) + 1;
	if (operator == '>' && line[i] == '<' && original_index > 0)
		if (first_case_error(line, &i))
			return (1);
	if (operator == '<' && line[i] == '>' && original_index > 0)
		if (first_case_error(line, &i))
			return (1);
	if (line[i] == operator)
		if (second_case_error(line, &i, operator))
			return (1);
	return (0);
}

static int	double_operator_error(char *line, int original_index)
{
	if (check_if_operator(line, '>', original_index))
		return (1);
	else if (check_if_operator(line, '<', original_index))
		return (1);
	return (0);
}

static int operator_with_pipe(char *line)
{
	int	i;

	i = 1;
	i += skip_space(&line[i]);
	if (line[i] == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (line[i] == '\0')
	{
		printf("syntax error near unexpected token 'newline'\n");
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
		if (line[i] == '\'' || line[i] == '\"')
			i += skip_in_between(&line[i], line[i]);
		else if (line[i] == '<' || line[i] == '>')
		{
			if (simple_operator_error(&line[i]))
				return (1);
			else if (double_operator_error(&line[i], i))
				return (1);
			else if (operator_with_pipe(&line[i]))
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}
