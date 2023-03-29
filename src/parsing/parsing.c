/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/29 13:40:39 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_if_exec_needed(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == '\n' || line[i] == ' ' || line[i] == '	'))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	check_error(char **line, t_line *all_cmd, t_env_main *main_env)
{
	(void) all_cmd;
	if (input_operator_check(*line))
		return (1);
	if (check_if_exec_needed(*line))
		return (1);
	*line = replace_global_variable(*line, main_env);
	if (*line == NULL)
		return (-1);
	return (0);
}

int	parsing(char *line, t_line *all_cmd, t_env_main *main_env)
{
	int	error;

	if (line[0] == '\0')
		return (1);
	error = check_error(&line, all_cmd, main_env);
	if (error)
		return (error);
	error = split_line(line, all_cmd);
	if (error == 0)
		convert_in_3d_array(all_cmd);
	free_cmd_struct(all_cmd);
	return (error);
}
