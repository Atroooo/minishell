/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_operator_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:31:27 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/04 13:56:35 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	first_case_error(char *line, int *i)
{
	char	operator;

	operator = line[*i];
	*i += skip_space(&line[*i +1]) + 1;
	if (line[*i] == '\0')
	{
		ft_putstr_fd("bash: syntax error near unexpected token ", 2);
		ft_putchar_fd('`', 2);
		ft_putchar_fd(operator, 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
	return (0);
}

static int	second_case_error(char *line, int *i, char operator)
{
	*i += skip_space(&line[*i + 1]) + 1;
	if (line[*i] == '\0' && line[*i])
		return (ft_putendl_fd("bash: syntax error near \
			unexpected token 'newline'", 2), 1);
	if (line[*i] == '<' || line[*i] == '>')
	{
		*i += skip_space(&line[*i + 1]) + 1;
		if (line[*i] == '<' || line[*i] == '>')
		{
			ft_putstr_fd("bash: syntax error near unexpected token ", 2);
			ft_putchar_fd('`', 2);
			ft_putchar_fd(operator, 2);
			ft_putchar_fd(operator, 2);
			ft_putendl_fd("`", 2);
		}
		else
		{
			ft_putstr_fd("bash: syntax error near unexpected token ", 2);
			ft_putchar_fd('`', 2);
			ft_putchar_fd(operator, 2);
			ft_putendl_fd("`", 2);
		}
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
