/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_operator_error_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:55:27 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/15 14:33:49 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	simple_operator_error(char *line)
{
	int	i;
	int	space;

	space = skip_space(&line[1]);
	i = space + 1;
	if (line[1] == '\0' || line[i] == '\0')
	{
		ft_printf(2, "bash: syntax error near unexpected token 'newline'\n");
		return (1);
	}
	if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && space)
	{
		ft_printf(2, "bash: syntax error near unexpected token `%s'\n", line[i]);
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
		ft_printf(2, "syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (line[i] == '\0')
	{
		ft_printf(2, "syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
