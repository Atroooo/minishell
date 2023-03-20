/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:07:14 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/20 08:55:14 by vgonnot          ###   ########.fr       */
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
		if (line[i] == '|')
		{
			nbr_split += 1;
			if (line[i] == line[i + 1])
				i++;
		}
		i++;
	}
	return (nbr_split);
}

void	set_up_newlst(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->flag = NULL;
	cmd->content = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
}

void	set_up_arg(char *line, t_cmd *cmd, t_line *all_cmd)
{
	int	i;
	int	no_command;

	no_command = TRUE;
	i = 0;
	set_up_newlst(cmd);
	while (line[i] != '\0')
	{
		i += skip_space(&line[i]);
		if (line[i] == '<' || line[i] == '>')
			i += get_file(&line[i], cmd);
		else if (no_command == TRUE)
			i += get_cmd(&line[i], &no_command, cmd);
		else if (line[i] == '-')
			i += get_flag(&line[i], cmd, all_cmd);
		else
			i += get_content(&line[i], cmd);
	}
}

void	split_line(char *line, t_line *all_cmd)
{
	char	**splitted_line;
	int		i;

	i = 0;
	all_cmd->all_cmd = NULL;
	splitted_line = ft_split(line, '|');
	if (splitted_line == NULL)
		exit (1);
	all_cmd->nbr_cmd = count_split(line);
	all_cmd->cmd = malloc(sizeof(t_cmd) * (all_cmd->nbr_cmd));
	if (all_cmd->cmd == NULL)
	{
		ft_free_2d_array(splitted_line);
		exit(1);
	}
	while (splitted_line[i] != NULL)
	{
		set_up_arg(splitted_line[i], &all_cmd->cmd[i], all_cmd);
		i++;
	}
	ft_free_2d_array(splitted_line);
}
