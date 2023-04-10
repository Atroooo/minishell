/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:40 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/10 15:48:54 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	setup_heredoc(t_env_pipe *st, t_line *all_cmd)
{
	char	*outfile;
	int		temp_pipe[2];

	pipe(temp_pipe);
	st->infile = temp_pipe[0];
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
	close(temp_pipe[1]);
	st->nbr_cmd = 1;
	return (1);
}

static char	*heredoc_parsing(t_line *all_cmd)
{
	char	*delimiter;
	char	*get_str;

	delimiter = get_delimiter(lst_last(all_cmd->infile)->data);
	if (!delimiter)
		return (NULL);
	get_str = get_next_line(0);
	if (get_str == NULL)
	{
		ft_printf("End of file : the delimiter was %s\n", delimiter);
		free(delimiter);
		return (NULL);
	}
	else if (ft_strcmp(delimiter, get_str) == 0)
	{
		free(delimiter);
		free(get_str);
		return (NULL);
	}
	free(delimiter);
	return (get_str);
}

static int	heredoc_loop(t_env_pipe *st, t_line *all_cmd)
{
	char	*str_print;
	char	*tmp_str;

	str_print = NULL;
	while (1)
	{
		ft_printf("heredoc> ");
		tmp_str = heredoc_parsing(all_cmd);
		if (!tmp_str)
			break ;
		else
		{
			str_print = ft_strnjoin(str_print, tmp_str, ft_strlen(tmp_str));
			if (!str_print)
				return (free(st), -1);
			free(tmp_str);
		}
	}
	if (!str_print)
		return (-1);
	write(st->infile, str_print, ft_strlen(str_print));
	free(str_print);
	return (1);
}

int	heredoc(t_env_pipe *st, t_line *all_cmd)
{
	int		return_value;

	if (!all_cmd->infile || !lst_last(all_cmd->infile)->data || \
		ft_strnstr(lst_last(all_cmd->infile)->data, "<<", 2) == 0)
		return (0);
	return_value = heredoc_loop(st, all_cmd);
	if (return_value == -1)
		return (-1);
	return (return_value);
}
