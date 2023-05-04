/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:39:48 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/04 15:20:10 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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

int	setup_outfile(t_env_pipe *st, char *file_raw)
{
	char	*file_name;

	if (!file_raw)
		return (0);
	file_name = setup_file(file_raw);
	if (!file_name)
		return (0);
	if (ft_strnstr(file_raw, ">>", 2) != NULL)
	{
		st->outfile = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (st->outfile == -1)
			return (free(st), 0);
		free(file_name);
		return (1);
	}
	else if (ft_strnstr(file_raw, ">", 1) != NULL)
	{
		st->outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (st->outfile == -1)
			return (free(st), 0);
		free(file_name);
		return (1);
	}
	return (0);
}

int	setup_infile(t_env_pipe *st, char *file_raw)
{
	char	*file_name;

	if (!file_raw)
		return (0);
	if (ft_strnstr(file_raw, "<<", 2) != NULL)
		return (1);
	file_name = setup_file(file_raw);
	if (!file_name)
		return (0);
	st->infile = open(file_name, O_RDWR);
	if (st->infile == -1 && st->hdoc == 0)
	{
		ft_putstr_fd("Cannot open file : ", 2);
		ft_putendl_fd(file_name, 2);
		free(file_name);
		free(st);
		return (0);
	}
	else if (st->infile == -1 && st->hdoc == 1)
		st->error_msg = -1;
	free(file_name);
	return (1);
}

static int	setup_pipe_files(t_line *all_cmd, t_env_pipe *st)
{
	if (st->input == 1)
	{
		if (!setup_infile(st, lst_last(all_cmd->infile)->data))
			return (0);
	}
	else
		st->infile = 0;
	if (st->output == 1)
	{
		if (!setup_outfile(st, lst_last(all_cmd->outfile)->data))
			return (0);
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
	else
	{
		if (!setup_pipe_files(all_cmd, st))
			return (0);
		return (1);
	}
	return (0);
}
