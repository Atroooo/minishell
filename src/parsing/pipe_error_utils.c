/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:00:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/04 15:04:11 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_if_pipe(char *line, int *consecutive_pipe, int *quote)
{
	int	i;

	i = 0;
	while (line && line[i] == '|')
	{
		*quote = 0;
		*consecutive_pipe += 1;
		i++;
	}
	return (i);
}

int	check_char(char c, int *pipe, int *consecutive_pipe, int *only_space)
{
	if (c == '|')
	{
		*pipe = 1;
		*consecutive_pipe += 1;
	}
	else if (c == '\0')
		return (0);
	else
	{
		*only_space = 0;
		*consecutive_pipe = 0;
	}
	return (1);
}

int	first_error_case(int consecutive_pipe, int only_space, int quote)
{
	if ((consecutive_pipe == 2 && only_space == 1 && quote == 0) \
				|| consecutive_pipe > 3)
		return (1);
	return (0);
}

int	var_init(int *quote, int *consecutive_pipe, int *only_space, int *i)
{
	*quote = 0;
	*consecutive_pipe = 0;
	*only_space = 1;
	*i = 1;
	return (0);
}

int	check_if_quote_increment(char c, int *quote)
{
	if (c == '\'' || c == '\"')
	{
		*quote = 1;
		return (1);
	}
	return (0);
}
