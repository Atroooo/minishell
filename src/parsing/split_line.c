/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:07:14 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/11 17:33:38 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	get_content(char *line, t_cmd *cmd)
{
	return (0);
}

static void	set_cmd_struct(char *line, t_line *all_cmd)
{
	int	line_index;
	int	cmd_index;

	line_index = 0;
	cmd_index = 0;
	while (line[line_index] != '\0' && cmd_index < 1)
	{
		line_index += get_cmd(&line[line_index], &all_cmd->cmd[cmd_index]);
		line_index += get_flag(&line[line_index], &all_cmd->cmd[cmd_index]);
		line_index += get_content(&line[line_index], &all_cmd->cmd[cmd_index]);
		all_cmd->cmd[cmd_index].separator = line[line_index];
		if (all_cmd->cmd[cmd_index].separator == '\0')
			break ;
		cmd_index += 1;
		line_index += 1;
	}
}

void	split_line(char *line, t_line *all_cmd)
{
	int	nbr_split;

	nbr_split = count_split(line);
	all_cmd->cmd = malloc(sizeof(t_cmd) * (nbr_split + 1));
	if (all_cmd->cmd == NULL)
		exit(1); //A GERER
 	set_cmd_struct(line, all_cmd);
}
