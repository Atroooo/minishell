/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/28 09:23:41 by vgonnot          ###   ########.fr       */
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

int	check_error(char **line, t_line *all_cmd, t_env_var *env_list)
{
	(void) all_cmd;
	if (input_operator_check(*line))
		return (1);
	if (check_if_exec_needed(*line))
		return (1);
	*line = replace_global_variable(*line, env_list);
	if (*line == NULL)
		return (-1);
	return (0);
}

int	parsing(char *line, t_line *all_cmd, t_env_var *env_list)
{
	int	error;

	if (line[0] == '\0')
		return (1);
	error = check_error(&line, all_cmd, env_list);
	if (error)
		return (error);
	error = split_line(line, all_cmd);
	if (error == 0)
		convert_in_3d_array(all_cmd);
	free_cmd_struct(all_cmd);
	return (error);
}
