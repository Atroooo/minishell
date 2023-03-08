/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/07 15:13:48 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_error(char **cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line[i] != NULL)
	{
		if (input_operator_check(cmd_line[i]))
			printf("bash: syntax error near unexpected token\n");
		i++;
	}
	return (0);
}

void	parsing(char *line)
{
	char	**cmd_line;

	cmd_line = ft_split(line, ' ');
	check_error(cmd_line);
}
