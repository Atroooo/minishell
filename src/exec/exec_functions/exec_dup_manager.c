/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:20:10 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/17 15:39:23 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	get_dup_single_done(t_env_pipe *st)
{
	if (st->nbr_cmd == 1)
	{
		if (st->infile != 0)
			if (dup2(st->infile, STDIN_FILENO) == -1)
				return (0);
		if (st->outfile != 1)
			if (dup2(st->outfile, STDOUT_FILENO) == -1)
				return (0);
		return (1);
	}
	return (1);
}

static int	get_first_dup_done(t_env_pipe *st, t_line *all_cmd)
{
	if (check_spe_infile(st, all_cmd))
		if (!setup_spe_infile(st, all_cmd))
			return (0);
	if (dup2(st->infile, STDIN_FILENO) == -1)
		return (0);
	if (check_spe_outfile(st, all_cmd))
	{
		if (!open_outfile(st, all_cmd))
			return (0);
		if (dup2(st->outfile, STDOUT_FILENO) == -1)
			return (0);
		return (1);
	}
	else
		if (dup2(st->fd[st->actual_pipe][1], STDOUT_FILENO) == -1)
			return (0);
	return (1);
}

static int	get_last_dup_done(t_env_pipe *st, t_line *all_cmd)
{
	if (check_spe_infile(st, all_cmd) || \
		(st->hdoc == 1 && all_cmd->all_cmd[0][0] == NULL))
	{
		if (st->hdoc != 1 && !setup_spe_infile(st, all_cmd))
			return (0);
		if (dup2(st->infile, STDIN_FILENO) == -1)
			return (0);
	}
	else
		if (dup2(st->fd[st->actual_pipe - 1][0], STDIN_FILENO) == -1)
			return (0);
	if (st->output == 1)
	{
		if (!setup_outfile(st, lst_last(all_cmd->outfile)->data, all_cmd))
			return (0);
	}
	else
		st->outfile = 1;
	if (dup2(st->outfile, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

static int	get_dup_done(t_env_pipe *st, t_line *all_cmd)
{
	if (check_spe_infile(st, all_cmd))
	{
		if (!setup_spe_infile(st, all_cmd))
			return (0);
		if (dup2(st->infile, STDIN_FILENO) == -1)
			return (0);
	}
	else
		if (dup2(st->fd[st->actual_pipe - 1][0], STDIN_FILENO) == -1)
			return (0);
	if (check_spe_outfile(st, all_cmd))
	{
		if (!open_outfile(st, all_cmd))
			return (0);
		if (dup2(st->outfile, STDOUT_FILENO) == -1)
			return (0);
	}
	else
	{
		if (dup2(st->fd[st->actual_pipe][1], STDOUT_FILENO) == -1)
			return (0);
		st->outfile = st->fd[st->actual_pipe][1];
	}
	return (1);
}

int	dup_manager(t_env_pipe *st, t_line *all_cmd)
{
	if (!get_dup_single_done(st))
		return (0);
	if (st->nbr_cmd > 1)
	{
		if (st->actual_pipe == 0)
		{
			if (!get_first_dup_done(st, all_cmd))
				return (0);
		}
		else if (st->actual_pipe == st->nbr_cmd - 1)
		{
			if (!get_last_dup_done(st, all_cmd))
				return (0);
		}
		else
		{
			if (!get_dup_done(st, all_cmd))
				return (0);
		}
	}
	return (1);
}
