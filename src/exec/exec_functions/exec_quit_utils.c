/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_quit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:50:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/15 14:34:15 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	close_function(t_env_pipe *st)
{
	int	i;

	if (st->infile != 0)
		close(st->infile);
	if (st->outfile != 1)
		close(st->outfile);
	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

int	quit_function(t_env_pipe *st, int error_code)
{
	close_function(st);
	free_pipe(st);
	if (error_code == 0)
		ft_printf(2, "Error : %s\n", strerror(errno));
	else if (error_code == 1)
		ft_printf(2, "Error : Fork\n");
	else if (error_code == 2)
		return (1);
	return (0);
}

void	free_pipe(t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		free(st->fd[i]);
		i++;
	}
	free(st->pid);
	free(st->fd);
	free(st);
}

void	free_env(t_env_pipe *st, int i)
{
	if (i >= 0)
	{
		while (i >= 0)
		{
			if (st->fd[i] != NULL)
				free(st->fd[i]);
			i--;
		}
		free(st->pid);
		free(st->fd);
	}
	free(st);
}
