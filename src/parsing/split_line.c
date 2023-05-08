/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:07:14 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/08 09:48:51 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	manage_get_content(int *error, int *i, char *line, t_cmd *cmd)
{
	*error = get_element(i, &get_content, &line[*i], cmd);
	if (*error == 0 \
		&& ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->content->data)) == 0)
		return (TRUE);
	return (FALSE);
}

int	set_up_arg(char *line, t_cmd *cmd)
{
	int	i;
	int	error;
	int	no_command;
	int	is_echo;
	int	y;

	y = 0;
	i = initialize_variable(cmd, &error, &no_command, &is_echo);
	while (line[i] != '\0' && error == 0)
	{
		i += skip_space(&line[i]);
		if (line[i] == '<' || line[i] == '>')
			error = get_element_file(&i, &line[i], cmd, y++);
		else if (check_if_get_cmd(line[i], &no_command, error))
			error = get_element(&i, &get_cmd, &line[i], cmd);
		else if (line[i] == '-' && error == 0 && is_echo == FALSE)
			error = get_element(&i, &get_flag, &line[i], cmd);
		else if (line[i] != '\0' && error == 0)
			is_echo = manage_get_content(&error, &i, line, cmd);
	}
	if (error == -1)
		free_single_cmd(cmd);
	return (error);
}

int	initialize_value(t_line *all_cmd, char **splitted_line)
{
	int	i;

	i = 0;
	all_cmd->nbr_cmd = count_split(splitted_line);
	all_cmd->cmd = malloc(sizeof(t_cmd) * (all_cmd->nbr_cmd));
	while (i < all_cmd->nbr_cmd)
	{
		all_cmd->cmd[i].cmd = NULL;
		all_cmd->cmd[i].content = NULL;
		all_cmd->cmd[i].flag = NULL;
		all_cmd->cmd[i].infile = NULL;
		all_cmd->cmd[i].outfile = NULL;
		i++;
	}
	all_cmd->infile = NULL;
	all_cmd->outfile = NULL;
	if (all_cmd->cmd == NULL)
		return (-1);
	return (0);
}

int	split_line(char *line, t_line *all_cmd)
{
	char	**splitted_line;
	int		i;
	int		error;

	error = 0;
	i = 0;
	all_cmd->all_cmd = NULL;
	all_cmd->nbr_cmd = 0;
	all_cmd->cmd = NULL;
	splitted_line = split_skip_quote(line);
	if (splitted_line == NULL)
		return (-1);
	error = initialize_value(all_cmd, splitted_line);
	while (error == 0 && splitted_line[i] != NULL)
	{
		error = set_up_arg(splitted_line[i], &all_cmd->cmd[i]);
		i++;
	}
	if (error)
		while (--i >= 0)
			free_single_cmd(&all_cmd->cmd[i]);
	ft_free_2d_array(splitted_line);
	return (error);
}
