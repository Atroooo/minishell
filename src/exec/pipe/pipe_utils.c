/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:39:48 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/30 14:16:21 by lcompieg         ###   ########.fr       */
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

int	set_up_struct(t_env_pipe *st, t_line *all_cmd, int argc)
{
	st->nbr_cmd = argc;
	st->hdoc = heredoc(st, all_cmd);
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
/*A protect*/

char	*setup_file(char *raw_file)
{
	char	*file;

	if (!raw_file)
		return (NULL);
	file = ft_strtrim(raw_file, "<> ");
	if (!file)
		return (NULL);
	return (file);
}

static int	setup_pipe_files(t_line *all_cmd, t_env_pipe *st)
{
	char	*infile;
	char	*outfile;

	if (st->input == 1)
	{
		infile = setup_file(lst_last(all_cmd->infile)->data);
		if (!infile)
			return (0);
		st->infile = open(infile, O_RDWR);
		if (st->infile == -1)
			return (ft_printf("Cannot open file : %s\n", infile), free(st), 0);
		free(infile);
	}
	else
		st->infile = 0;
	if (st->output == 1)
	{
		outfile = setup_file(lst_last(all_cmd->outfile)->data);
		if (!outfile)
			return (0);
		st->outfile = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (st->outfile == -1)
			return (quit_function(st, 0));
		free(outfile);
	}
	else
		st->outfile = 1;
	return (1);
}

int	open_files(t_env_pipe *st, t_line *all_cmd)
{
	if (st->input == 0 && st->output == 0)
	{
		st->infile = 0;
		st->outfile = 1;
		return (1);
	}
	else if (all_cmd->infile != NULL && \
		ft_strnstr(lst_last(all_cmd->infile)->data, "<<", 2) != 0)
	{
		if (!setup_heredoc(st, all_cmd))
			return (0);
		return (1);
	}
	else
	{
		if (!setup_pipe_files(all_cmd, st))
			return (0);
		return (1);
	}
	return (0);
}
