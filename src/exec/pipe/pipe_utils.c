/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:39:48 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/10 10:58:53 by lcompieg         ###   ########.fr       */
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

static int	setup_inout(t_env_pipe *st, char *file_raw, int s)
{
	char	*file_name;

	file_name = setup_file(file_raw);
	if (!file_name)
		return (0);
	if (s == 0)
	{
		st->infile = open(file_name, O_RDWR);
		if (st->infile == -1)
			return (ft_printf("Cannot open file : %s\n", file_name), \
				free(st), 0);
		free(file_name);
		return (1);
	}
	if (s == 1)
	{
		st->outfile = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (st->outfile == -1)
			return (free(st), 0);
		free(file_name);
		return (1);
	}
	return (0);
}

static int	setup_pipe_files(t_line *all_cmd, t_env_pipe *st)
{
	if (st->input == 1)
	{
		if (!setup_inout(st, lst_last(all_cmd->infile)->data, 0))
			return (0);
	}
	else
		st->infile = 0;
	if (st->output == 1)
	{
		if (!setup_inout(st, lst_last(all_cmd->outfile)->data, 1))
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
	else if (all_cmd->infile != NULL && lst_last(all_cmd->infile)->data && \
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
