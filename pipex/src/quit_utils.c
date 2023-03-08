/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:50:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 07:52:07 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	close_function(t_env *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd - 1)
	{
		close(st->fd[i][0]);
		close(st->fd[i][1]);
		i++;
	}
}

void	quit_function(t_env *st, int error_code)
{
	close_function(st);
	free_pipe(st);
	if (error_code == 0)
		exit(ft_printf("Error : %s\n", strerror(errno)));
	else if (error_code == 1)
		exit(ft_printf("Error : Fork\n"));
	exit(EXIT_FAILURE);
}

void	error_execve(char **arg_vec, char *path, t_env *st)
{
	ft_free_2d_array(arg_vec);
	free(path);
	quit_function(st, -1);
}

void	free_pipe(t_env *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd - 1 && st->fd && st->fd[i])
	{
		free(st->fd[i]);
		i++;
	}
	if (st->pid != NULL)
		free(st->pid);
	if (st->fd != NULL)
		free(st->fd);
	if (st != NULL)
		free(st);
}

void	free_env_exit(t_env *st, int i)
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
	exit(EXIT_FAILURE);
}
