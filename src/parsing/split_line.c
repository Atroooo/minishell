/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neoff <neoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:07:14 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/20 16:03:27 by neoff            ###   ########.fr       */
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

int	get_element(int *i, int (*get)(char *, t_cmd *), char *line, t_cmd *cmd)
{
	int	temp;

	temp = get(&line[*i], cmd);
	if (temp == -1)
		return (-1);
	*i += temp;
	return (0);
}

int	set_up_arg(char *line, t_cmd *cmd, t_line *all_cmd)
{
	int	i;
	int	temp;
	int	no_command;

	no_command = TRUE;
	i = 0;
	set_up_newlst(cmd);
	while (line[i] != '\0')
	{
		i += skip_space(&line[i]);
		if (line[i] == '<' || line[i] == '>')
		{
			if (get_element(&i, &get_file, &line[i], cmd))
				return (-1);
		}
		else if (no_command == TRUE)
		{
			if (get_element(&i, &get_cmd, &line[i], cmd))
				return (-1);
			no_command = 0;
		}
		else if (line[i] == '-')
		{
			printf("test");
			if (get_element(&i, &get_flag, &line[i], cmd))
				return (-1);
		}
		else
		{
			if (get_element(&i, &get_content, &line[i], cmd))
				return (-1);
		}
		printf("%c\n", line[i]);
	}
	return (0);
}

int	split_line(char *line, t_line *all_cmd)
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
