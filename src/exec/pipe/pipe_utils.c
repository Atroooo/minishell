/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:39:48 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/27 16:11:51 by lcompieg         ###   ########.fr       */
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

int	set_up_struct(t_env_pipe *st, int argc)
{
	if (argc > 3)
		st->nbr_cmd = argc - 3;
	else
		st->nbr_cmd = 1;
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

static int	setup_heredoc(int argc, char **argv, t_env_pipe *st)
{
	st->infile = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (st->infile == -1)
	{
		ft_printf("Cannot open file : %s\n", argv[1]);
		free(st);
		return (0);
	}
	st->outfile = open(argv[argc -1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (st->outfile == -1)
		quit_function(st, 0);
	return (1);
}

static int	setup_pipe_files(int argc, char **argv, t_env_pipe *st)
{
	st->infile = open(argv[1], O_RDWR);
	if (st->infile == -1)
	{
		ft_printf("Cannot open file : %s\n", argv[1]);
		free(st);
		return (0);
	}
	st->outfile = open(argv[argc -1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (st->outfile == -1)
		quit_function(st, 0);
	return (1);
}

int	open_files(int argc, char **argv, t_env_pipe *st)
{
	int	hdoc;

	if (!argv[1])
	{
		st->infile = 0;
		st->outfile = 1;
		return (1);
	}
	hdoc = ft_strcmp(argv[1], "<<");
	if (hdoc == 0)
	{
		if (!setup_heredoc(argc, argv, st))
			return (0);
	}
	else
	{
		if (!setup_pipe_files(argc, argv, st))
			return (0);
	}
	return (1);
}
