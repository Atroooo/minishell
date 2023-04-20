/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_quit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:50:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/20 14:34:30 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	close_function(t_env_pipe *st)
{
	int	i;

	i = 0;
	if (st->hdoc == 1)
		return ;
	while (i < st->nbr_cmd - 1)
	{
		close(st->fd[i][0]);
		close(st->fd[i][1]);
		i++;
	}
	if (st->infile != 0)
		close(st->infile);
	if (st->outfile != 1)
		close(st->outfile);
}

int	quit_function(t_env_pipe *st, int error_code)
{
	close_function(st);
	free_pipe(st);
	if (error_code == 0)
		ft_printf("Error : %s\n", strerror(errno));
	else if (error_code == 1)
		ft_printf("Error : Fork\n");
	else if (error_code == 2)
		return (1);
	return (0);
}

void	free_pipe(t_env_pipe *st)
{
	int	i;

	i = 0;
	if (st->hdoc == 1)
	{
		free(st->pid);
		free(st);
		return ;
	}
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
			free(st->fd[i]);
			i--;
		}
		free(st->pid);
		free(st->fd);
	}
	free(st);
}
