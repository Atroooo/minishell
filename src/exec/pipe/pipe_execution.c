/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:42:03 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/07 22:54:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	fork_declaration(char **argv, char *env[], t_env_pipe *st, int i)
{
	st->pid[i] = fork();
	if (st->pid[i] == -1)
		return (quit_function(st, 1));
	if (st->pid[i] < 0)
		return (quit_function(st, 1));
	if (st->pid[i] == 0)
	{
		if (!dup_manager(st))
			return (0);
		if (!get_exec_done(argv[i], env, st))
			return (0);
	}
	return (1);
}

static void	wait_for_process(t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		waitpid(st->pid[i], NULL, 0);
		i++;
	}
}

static void	end_the_progam(t_env_pipe *st)
{
	close_function(st);
	wait_for_process(st);
	free_pipe(st);
}

int	execution(char **argv, char *env[], t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		if (!fork_declaration(argv, env, st, i))
			return (0);
		st->actual_pipe += 1;
		i++;
	}
	end_the_progam(st);
	return (1);
}
