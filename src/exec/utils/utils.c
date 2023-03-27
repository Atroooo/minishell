/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:07:49 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/27 15:51:42 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	cmd_size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	get_total_cmd(t_line *all_cmd)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (all_cmd->all_cmd[i])
	{
		j = 0;
		while (all_cmd->all_cmd[i][j])
		{
			count++;
			j++;
		}
		i++;
	}
	return (count);
}
