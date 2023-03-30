/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:40 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/30 14:13:24 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*Need protect*/
/*Ajouter toute la chaine au fur et a mesure avec les \n*/
int	setup_heredoc(t_env_pipe *st, t_line *all_cmd)
{
	int	temp_pipe[2];

	pipe(temp_pipe);
	st->infile = temp_pipe[0];
	if (st->output == 0)
		st->outfile = 1;
	else
	{
		st->outfile = open(lst_last(all_cmd->outfile)->data, \
			O_RDWR | O_CREAT | O_APPEND, 0644);
		if (st->outfile == -1)
			quit_function(st, 0);
	}
	close(temp_pipe[1]);
	return (1);
}

static char	*get_delimiter(char *str)
{
	char	*delimiter;

	delimiter = ft_strtrim(str, "< ");
	if (!delimiter)
		return (NULL);
	return (delimiter);
}

static int	heredoc_parsing(t_env_pipe *st, t_line *all_cmd)
{
	char	*delimiter;
	char	*get_str;

	delimiter = get_delimiter(lst_last(all_cmd->infile)->data);
	get_str = get_next_line(0);
	if (get_str == NULL)
	{
		ft_printf("End of file : the delimiter was %s\n", delimiter);
		return (1);
	}
	else if (ft_strcmp(delimiter, get_str) == 0)
	{
		free(get_str);
		return (1);
	}
	write(st->infile, get_str, ft_strlen(get_str));
	free(get_str);
	return (0);
}

int	heredoc(t_env_pipe *st, t_line *all_cmd)
{
	if (!all_cmd->infile)
		return (0);
	if (ft_strnstr(lst_last(all_cmd->infile)->data, "<<", 2) == 0)
		return (0);
	st->nbr_cmd = 1;
	while (1)
	{
		ft_printf("heredoc> ");
		if (heredoc_parsing(st, all_cmd) == 1)
			break ;
	}
	return (1);
}
