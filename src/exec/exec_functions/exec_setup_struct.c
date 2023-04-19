/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:17:52 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/19 20:46:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	setup_pipe(t_env_pipe *st)
{
	int	i;

	i = 0;
	if (st->hdoc == 1)
		return (1);
	while (i < st->nbr_cmd)
	{
		st->fd[i] = malloc(sizeof(int) * 2);
		if (st->fd[i] == NULL || pipe(st->fd[i]) == -1)
		{
			free_env(st, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	setup_struct_cmd(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env)
{
	st->nbr_cmd = all_cmd->nbr_cmd;
	st->hdoc = heredoc(st, all_cmd, main_env);
	if (st->hdoc == -1)
		return (0);
	st->actual_pipe = 0;
	st->pid = malloc(sizeof(int) * (st->nbr_cmd + 1));
	if (st->pid == NULL)
	{
		free_env(st, -1);
		return (0);
	}
	if (st->hdoc != 1)
	{
		st->fd = malloc(sizeof(int *) * (st->nbr_cmd));
		if (st->fd == NULL)
		{
			free(st->pid);
			free_env(st, -1);
			return (0);
		}
		if (!setup_pipe(st))
			return (0);
	}
	
	return (1);
}
