/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:07:14 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/09 12:41:18 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		i++;
	}
	return (i);
}

static int	count_split(char *line)
{
	int	i;
	int	nbr_split;

	nbr_split = 1;
	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '|' || line[i] == ';' || line[i] == '&')
		{
			nbr_split += 1;
			if (line[i] == line[i + 1])
				i++;
		}
		i++;
	}
	return (nbr_split);
}

static int	get_content(char *line, t_cmd *cmd)
{
	return (0);
}

static int	get_flag(char *line, t_cmd *cmd)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (line[i] & (line[i] == ' ' && line[i + 1] != '-'))
	{
		
	}
	// while (line[i] != '\0' && line[i] == ' ')
	// 	i++;
	// while (line[i] != '\0' && line[i] != ' ')
	// {
	// 	cmd->flag[y] = line[i];
	// 	i++;
	// 	y++;
	// }
	return (0);
}

static int	get_cmd(char *line, t_cmd *cmd)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	cmd->cmd = malloc(sizeof(char) * (get_len(&line[i]) + 1));
	if (cmd->cmd == NULL)
		exit(1); //A GERER PLUS TARD
	while (line[i] != '\0' && line[i] != ' ')
	{
		cmd->cmd[y] = line[i];
		i++;
		y++;
	}
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	cmd->cmd[y] = '\0';
	return (i);
}

// static int	check_if_separator(char c, t_cmd *cmd)
// {
// 	if (c == '\0')
// 	{
// 		cmd->separator = '\0';
// 		return (1);
// 	}
// 	else if (c == '|')
// 	{
// 		cmd->separator = '|';
// 		return (1);
// 	}
// 	else if (c == ';')
// 	{
// 		cmd->separator = ';';
// 		return (1);
// 	}
// 	else if (c == '&')
// 	{
// 		cmd->separator = '&';
// 		return (1);
// 	}
// 	return (0);
// }

static void	set_cmd_struct(char *line, t_line *all_cmd)
{
	int	line_index;
	int	cmd_index;

	line_index = 0;
	cmd_index = 0;
	while (line[line_index] != '\0')
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
