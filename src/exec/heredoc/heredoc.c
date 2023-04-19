/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:40 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/19 17:43:01 by lcompieg         ###   ########.fr       */
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

static int	heredoc_loop(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env)
{
	char	*tmp_str;
	int		temp_pipe[2];

	pipe(temp_pipe);
	st->infile = temp_pipe[0];
	signal_handler_hdoc(main_env);
	while (1)
	{
		ft_printf("heredoc> ");
		tmp_str = heredoc_parsing(all_cmd);
		if (!tmp_str || main_env->exit_status == 255)
			break ;
		else
		{
			write(temp_pipe[1], tmp_str, ft_strlen(tmp_str));
			free(tmp_str);
		}
	}
	close(temp_pipe[1]);
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
