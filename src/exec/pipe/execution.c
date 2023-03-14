/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:42:03 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/14 11:02:52 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	fork_declaration(char **argv, char *env[], t_env_pipe *st, int i)
{	
	st->pid[i] = fork();
	if (st->pid[i] == -1)
	{
		free_env_exit(st, st->nbr_cmd - 1);
		return (0);
	}	
	if (st->pid[i] < 0)
		return (quit_function(st, 1));
	if (st->pid[i] == 0)
	{
		dup_manager(st);
		get_exec_done(argv, env, st);
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
	close(st->infile);
	close(st->outfile);
	close_function(st);
	wait_for_process(st);
	free_pipe(st);
}

void	execution(char **argv, char *env[], t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		if (!fork_declaration(argv, env, st, i))
		{
			quit_function(st, 0);
			return ;
		}	
		st->actual_pipe += 1;
		i++;
	}
	end_the_progam(st);
}
