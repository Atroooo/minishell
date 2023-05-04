/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_operator_error_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:55:27 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/04 13:58:50 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	simple_operator_error(char *line)
{
	int	i;
	int	space;

	i = 1;
	if (line[1] == '\0')
	{
		ft_putendl_fd("bash: syntax error near unexpected token 'newline'", 2);
		return (1);
	}
	space = skip_space(&line[i]);
	i += space;
	if ((line[i] == '<' || line[i] == '>') && space)
	{
		ft_putstr_fd("bash: syntax error near unexpected token ", 2);
		ft_putchar_fd('`', 2);
		ft_putchar_fd(line[i], 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
	return (0);
}

int	operator_with_pipe(char *line)
{
	int	i;

	i = 0;
	i += skip_space(&line[i]);
	if (line[i] == '|')
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (1);
	}
	else if (line[i] == '\0')
	{
		ft_putendl_fd("syntax error near unexpected token 'newline'", 2);
		return (1);
	}
	return (0);
}
