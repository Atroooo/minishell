/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execution_utils_bis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:27:02 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 16:27:19 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	is_executable(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	if (cmd[0][0] == '\0')
		return (0);
	return (1);
}

void	close_zero_one(void)
{
	close(0);
	close(1);
}
