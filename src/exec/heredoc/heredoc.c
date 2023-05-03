/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:40 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/03 17:51:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	setup_heredoc(t_env_pipe *st, t_line *all_cmd)
{
	char	*outfile;

	if (st->output == 0)
		st->outfile = 1;
	else
	{
		outfile = setup_file(lst_last(all_cmd->outfile)->data);
		if (!outfile)
			return (0);
		st->outfile = open(outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (st->outfile == -1)
			return (free(st), 0);
		free(outfile);
	}
	return (1);
}

int	heredoc(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env)
{
	int		return_value;

	if (!all_cmd->infile || !lst_last(all_cmd->infile)->data || \
		ft_strnstr(lst_last(all_cmd->infile)->data, "<<", 2) == 0)
		return (0);
	return_value = heredoc_loop(st, all_cmd, main_env);
	if (return_value == -1)
		return (-1);
	return (return_value);
}
