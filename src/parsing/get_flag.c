/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:19:23 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/13 13:46:01 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	end_of_flag(char c, char next_c)
{
	if (c == ' ' && next_c != ' ' && next_c != '-')
		return (1);
	return (0);
}

static int	count_number_flag(char *line)
{
	int	i;
	int	number_flag;

	number_flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-' )
		{
			if (line[i +1] == '-')
				i++;
			number_flag++;
		}
		if (end_of_flag(line[i], line[i + 1]))
			break ;
		i++;
	}
	return (number_flag);
}

static int	copy_flag(char *line, char *flag)
{
	int	i;
	int	y;

	y = 0;
	i = skip_space(line);
	while (line[i] != '\0' && line[i] != ' ')
	{
		flag[y] = line[i];
		y++;
		i++;
	}
	flag[y] = '\0';
	i += skip_space(line);
	return (i);
}

static int	copy_all_flag(char *line, t_cmd *cmd, int line_index, int nbr_flag)
{
	int	flag_index;

	flag_index = 0;
	while (flag_index < nbr_flag)
	{
		cmd->flag[flag_index] = \
					malloc(sizeof(char) * count_len(&line[line_index]) + 1);
		if (cmd->flag[flag_index] == NULL)
			exit(1); //A GERER PLUS TARD
		line_index += copy_flag(&line[line_index], cmd->flag[flag_index]);
		flag_index++;
	}
	cmd->flag[flag_index] = NULL;
	if (line[line_index] == '\0')
		line_index -= 1;
	return (line_index);
}

int	get_flag(char *line, t_cmd *cmd)
{
	int	line_index;
	int	nbr_flag;

	line_index = skip_space(line);
	if (line[line_index] != '-')
		return (0);
	nbr_flag = count_number_flag(line);
	cmd->flag = malloc(sizeof(char *) * nbr_flag + 1);
	if (cmd->flag == NULL)
		exit(1); //A GERER PLUS TARD
	line_index += copy_all_flag(line, cmd, line_index, nbr_flag);
	return (line_index);
}
