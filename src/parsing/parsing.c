/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/21 10:00:06 by marvin           ###   ########.fr       */
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

void	parsing(char *line, t_line *all_cmd)
{
	if (check_error(line, all_cmd))
		return ;
	split_line(line, all_cmd);
	convert_in_3d_array(all_cmd);
}
