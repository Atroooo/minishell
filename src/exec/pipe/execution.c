/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:42:03 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 13:36:36 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	fork_declaration(char **argv, char *env[], t_env *st, int i)
{	
	st->pid[i] = fork();
	if (st->pid[i] == -1)
		free_env_exit(st, st->nbr_cmd - 1);
	if (st->pid[i] < 0)
		quit_function(st, 1);
	if (st->pid[i] == 0)
	{
		dup_manager(st);
		get_exec_done(argv, env, st);
	}
}

void	wait_for_process(t_env *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		waitpid(st->pid[i], NULL, 0);
		i++;
	}
}

void	end_the_progam(t_env *st)
{
	close(st->infile);
	close(st->outfile);
	close_function(st);
	wait_for_process(st);
	free_pipe(st);
}

void	execution(char **argv, char *env[], t_env *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		fork_declaration(argv, env, st, i);
		st->actual_pipe += 1;
		i++;
	}
	end_the_progam(st);
}
