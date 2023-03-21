/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/21 10:15:12 by marvin           ###   ########.fr       */
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

int	parsing(char *line, t_line *all_cmd, char *env[], t_env_main *main_env)
{
	char		**cmd_line;
	char		**strr;
	int			error;
	if (check_error(line, all_cmd))
		return 1;
	error = split_line(line, all_cmd);
	if (error == 0)
		error = convert_in_3d_array(all_cmd);
	free_cmd_struct(all_cmd);
	return (error);
}
