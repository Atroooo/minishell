/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:20:10 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/12 16:59:38 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	get_dup_single_done(t_env_pipe *st)
{
	if (st->nbr_cmd == 1)
	{
		if (dup2(st->infile, STDIN_FILENO) == -1)
			return (quit_function(st, 0));
		if (dup2(st->outfile, STDOUT_FILENO) == -1)
			return (quit_function(st, 0));
		return (1);
	}
	return (1);
}

static int	get_first_dup_done(t_env_pipe *st)
{
	if (dup2(st->infile, STDIN_FILENO) == -1)
		return (quit_function(st, 0));
	if (dup2(st->fd[st->actual_pipe][1], STDOUT_FILENO) == -1)
		return (quit_function(st, 0));
	return (1);
}

static int	get_last_dup_done(t_env_pipe *st)
{
	if (dup2(st->fd[st->actual_pipe - 1][0], STDIN_FILENO) == -1)
		return (quit_function(st, 0));
	if (dup2(st->outfile, STDOUT_FILENO) == -1)
		return (quit_function(st, 0));
	return (1);
}

static int	get_dup_done(t_env_pipe *st)
{
	if (dup2(st->fd[st->actual_pipe - 1][0], STDIN_FILENO) == -1)
		return (quit_function(st, 0));
	if (dup2(st->fd[st->actual_pipe][1], STDOUT_FILENO) == -1)
		return (quit_function(st, 0));
	return (1);
}

int	dup_manager(t_env_pipe *st)
{
	if (!get_dup_single_done(st))
		return (0);
	if (st->nbr_cmd > 1)
	{
		if (st->actual_pipe == 0)
		{
			if (!get_first_dup_done(st))
				return (0);
		}
		else if (st->actual_pipe == st->nbr_cmd - 1)
		{
			if (!get_last_dup_done(st))
				return (0);
		}
		else
		{
			if (!get_dup_done(st))
				return (0);
		}
	}
	close_function(st);
	return (1);
}
