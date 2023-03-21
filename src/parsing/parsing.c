/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/21 22:27:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_error(char *line, t_line *all_cmd)
{
	(void) all_cmd;
	if (input_operator_check(line))
		return (1);
	return (0);
}

int	parsing(char *line, t_line *all_cmd)
{
	int	error;
	
	if (line[0] == '\0')
		return (1);
	if (check_error(line, all_cmd))
		return (1);
	split_line(line, all_cmd);
	error = 0;
	if (error == 0)
		convert_in_3d_array(all_cmd);
	free_cmd_struct(all_cmd);
	return (error);
}
