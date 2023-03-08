/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 08:20:10 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 11:21:46 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	get_first_dup_done(t_env *st)
{
	if (dup2(st->infile, STDIN_FILENO) == -1)
		quit_function(st, 0);
	if (dup2(st->fd[st->actual_pipe][1], STDOUT_FILENO) == -1)
		quit_function(st, 0);
	close(st->infile);
}

void	get_last_dup_done(t_env *st)
{
	if (dup2(st->fd[st->actual_pipe - 1][0], STDIN_FILENO) == -1)
		quit_function(st, 0);
	if (dup2(st->outfile, STDOUT_FILENO) == -1)
		quit_function(st, 0);
	close(st->outfile);
}

void	get_dup_done(t_env *st)
{
	if (dup2(st->fd[st->actual_pipe - 1][0], STDIN_FILENO) == -1)
		quit_function(st, 0);
	if (dup2(st->fd[st->actual_pipe][1], STDOUT_FILENO) == -1)
		quit_function(st, 0);
}

void	dup_manager(t_env *st)
{
	if (st->actual_pipe == 0)
		get_first_dup_done(st);
	else if (st->actual_pipe == st->nbr_cmd - 1)
		get_last_dup_done(st);
	else
		get_dup_done(st);
	close_function(st);
}
