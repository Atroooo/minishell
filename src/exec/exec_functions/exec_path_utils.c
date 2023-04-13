/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:05:58 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/13 12:29:34 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	path_is_null(t_env_pipe *st, char **cmd, char *cmd_s)
{
	char	*temp;

	temp = ft_strjoin(cmd_s, ": command not found\n");
	if (temp != NULL)
	{
		ft_putstr_fd(temp, 2);
		free(temp);
	}
	ft_free_2d_array(cmd);
	quit_function(st, -1);
	exit(0);
}

void	no_path(t_env_pipe *st, char **cmd)
{
	ft_free_2d_array(cmd);
	quit_function(st, 0);
	return ;
}
