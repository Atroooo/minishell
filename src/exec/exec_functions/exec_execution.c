/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:42:03 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/03 14:19:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	fork_declaration(t_line *all_cmd, char **cmd, \
	t_env_pipe *st, t_env_main *main_env)
{
	g_status = 255;
	st->pid[st->i] = fork();
	if (st->pid[st->i] < 0)
		return (quit_function(st, 1));
	if (st->pid[st->i] == 0)
	{
		if (!dup_manager(st, all_cmd))
			return (0);
		if (!get_exec_done(all_cmd, cmd, st, main_env))
			return (0);
	}
	return (1);
}

static void	wait_for_process(t_env_pipe *st, t_env_main *main_env)
{
	int	status;
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		waitpid(st->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		main_env->exit_status = WEXITSTATUS(status);
		g_status = main_env->exit_status;
	}
}

static void	end_the_progam(t_env_pipe *st, t_env_main *main_env)
{
	close_function(st);
	wait_for_process(st, main_env);
	free_pipe(st);
}

int	execution(t_line *all_cmd, t_env_pipe *st, t_env_main *main_env)
{
	st->i = 0;
	while (st->i < st->nbr_cmd)
	{
		if (!fork_declaration(all_cmd, all_cmd->all_cmd[st->i], st, main_env))
			return (0);
		st->actual_pipe += 1;
		st->i++;
	}
	end_the_progam(st, main_env);
	return (1);
}
