/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/03 17:28:32 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_if_exec_needed(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '\n' || line[i] == ' ' || line[i] == '	' \
			|| line[i] == ':' || line[i] == '!'))
	{
		if ((line[i] == ':' || line[i] == '!') \
			&& (line[i + 1] == ':' || line[i + 1] == '!'))
			return (0);
		i++;
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	check_error(char **line, t_line *all_cmd, t_env_main *main_env)
{
	int	error;

	(void) all_cmd;
	error = 0;
	*line = replace_global_variable(*line, main_env);
	if (*line == NULL)
		return (-1);
	*line = check_if_pipe_error(*line, main_env, &error);
	if (error)
		return (error);
	if (*line == NULL)
		return (-1);
	if (input_operator_check(*line))
		return (1);
	else if (check_if_exec_needed(*line))
		return (1);
	return (0);
}

char	*remove_tabs(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i += skip_in_between(&line[i], line[i]);
		else if (line[i] == 9)
			line[i] = ' ';
		else
			i++;
	}
	return (line);
}

int	parsing(char *line, t_line *all_cmd, t_env_main *main_env)
{
	int	error;

	if (line[0] == '\0')
		return (1);
	line = remove_tabs(line);
	error = check_error(&line, all_cmd, main_env);
	if (error)
	{
		free(line);
		return (error);
	}
	error = split_line(line, all_cmd);
	if (error == 0)
		error = convert_in_3d_array(all_cmd);
	free_cmd_struct(all_cmd);
	free(line);
	if (error == -1)
		return (error);
	return (error);
}
