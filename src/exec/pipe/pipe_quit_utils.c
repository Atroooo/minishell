/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_quit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:50:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/29 13:42:52 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	close_function(t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd - 1)
	{
		if (st->fd[i][0] != -1)
			close(st->fd[i][0]);
		if (st->fd[i][1] != -1)
			close(st->fd[i][1]);
		i++;
	}
}

int	quit_function(t_env_pipe *st, int error_code)
{
	close_function(st);
	free_pipe(st);
	if (error_code == 0)
		ft_printf("Error : %s\n", strerror(errno));
	else if (error_code == 1)
		ft_printf("Error : Fork\n");
	return (0);
}

int	error_execve(char **arg_vec, char *path, t_env_pipe *st)
{
	ft_free_2d_array(arg_vec);
	free(path);
	return (quit_function(st, -1));
}

void	free_pipe(t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd - 1 && st->fd && st->fd[i])
	{
		if (st->fd[i] != NULL)
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

void	free_env_exit(t_env_pipe *st, int i)
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