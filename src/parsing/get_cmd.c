/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:47:49 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/13 20:31:22 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	copy_cmd(char *line, t_cmd *cmd)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		cmd->cmd[y] = line[i];
		i++;
		y++;
	}
	cmd->cmd[y] = '\0';
	return (i);
}

int	get_cmd(char *line, t_cmd *cmd)
{
	int	line_index;

	line_index = skip_space(line);
	cmd->cmd = malloc(sizeof(char) * (count_len(&line[line_index]) + 1));
	if (cmd->cmd == NULL)
		exit(1); //A GERER PLUS TARD
	line_index += copy_cmd(&line[line_index], cmd);
	return (line_index);
}
