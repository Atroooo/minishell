/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:39:48 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/29 16:37:54 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	set_up_pipe(t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd - 1)
	{
		st->fd[i] = malloc(sizeof(int) * 2);
		if (st->fd[i] == NULL || pipe(st->fd[i]) == -1)
		{
			free_env_exit(st, i);
			return ;
		}
		i++;
	}
}

int	set_up_struct(t_env_pipe *st, int argc, char **argv)
{
	st->nbr_cmd = argc;
	st->hdoc = heredoc(st, argv);
	st->actual_pipe = 0;
	st->pid = malloc(sizeof(int) * (st->nbr_cmd + 1));
	if (st->pid == NULL)
	{
		free_env_exit(st, -1);
		return (0);
	}
	st->fd = malloc(sizeof(int *) * (st->nbr_cmd));
	if (st->fd == NULL)
	{
		free(st->pid);
		free_env_exit(st, -1);
		return (0);
	}
	set_up_pipe(st);
	return (1);
}

static int	setup_pipe_files(char **argv, t_env_pipe *st)
{
	if (st->input == 2)
	{
		st->infile = open(argv[1], O_RDWR);
		if (st->infile == -1)
		{
			ft_printf("Cannot open file : %s\n", argv[1]);
			return (free(st), 0);
		}
		st->outfile = 1;
		return (1);
	}
	else
	{
		st->infile = open(argv[0], O_RDWR);
		if (st->infile == -1)
		{
			ft_printf("Cannot open file : %s\n", argv[0]);
			return (free(st), 0);
		}
		st->outfile = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (st->outfile == -1)
			quit_function(st, 0);
		return (1);
	}
}

int	open_files(char **argv, t_env_pipe *st)
{
	if (st->input == 0 && st->output == 0)
	{
		st->infile = 0;
		st->outfile = 1;
		return (1);
	}
	if (ft_strnstr(argv[0], "<<", 2) != 0)
	{
		if (!setup_heredoc(argv, st))
			return (0);
	}
	else
	{
		if (!setup_pipe_files(argv, st))
			return (0);
	}
	return (1);
}
