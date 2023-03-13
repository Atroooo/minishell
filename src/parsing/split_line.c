/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:07:14 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/13 14:49:02 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

static void	set_cmd_struct(char *line, t_line *all_cmd)
{
	int	line_index;
	int	cmd_index;

	line_index = 0;
	cmd_index = 0;
	while (line[line_index] != '\0' && cmd_index < 1)
	{
		line_index += get_cmd(&line[line_index], &all_cmd->cmd[cmd_index]);
		//printf("index 1 = %d\n", line_index);
		line_index += get_flag(&line[line_index], &all_cmd->cmd[cmd_index]);
		//printf("index 2 = %d\n", line_index);
		line_index += get_content(&line[line_index], &all_cmd->cmd[cmd_index]);
		//printf("index 3 = %d\n", line_index);
		all_cmd->cmd[cmd_index].separator = line[line_index];
		if (all_cmd->cmd[cmd_index].separator == '\0')
			break ;
		cmd_index += 1;
		line_index += 1;
	}
}

void	print_parsing(t_line *all_cmd)
{
	int	i;

	i = 0;
	while (i < all_cmd->nbr_cmd)
	{
		printf("cmd = %s\n", all_cmd->cmd[i].cmd);
		printf("flag = ");
		ft_print_2d_array(all_cmd->cmd[i].flag);
		printf("\n");
		printf("content = ");
		ft_print_2d_array(all_cmd->cmd[i].content);
		printf("\n");
		i++;
	}
}

void	split_line(char *line, t_line *all_cmd)
{
	all_cmd->nbr_cmd = count_split(line);
	all_cmd->cmd = malloc(sizeof(t_cmd) * (all_cmd->nbr_cmd));
	if (all_cmd->cmd == NULL)
		exit(1); //A GERER
 	set_cmd_struct(line, all_cmd);
	//print_parsing(all_cmd);
}
