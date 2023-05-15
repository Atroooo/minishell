/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:40 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/15 13:36:24 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static char	*heredoc_parsing(t_line *all_cmd, int *hdoc_count, t_env_pipe *st)
{
	char	*get_str;

	get_str = readline("heredoc> ");
	st->delimiter = get_delimiter(get_delimiter_hdoc(all_cmd, *hdoc_count + 1));
	if (!st->delimiter)
		return (NULL);
	if (get_str == NULL)
	{
		*(hdoc_count) = get_nbr_hdoc(all_cmd);
		ft_printf("End of file : the delimiter was %s\n", st->delimiter);
		free(st->delimiter);
		return (NULL);
	}
	else if (ft_strcmp(st->delimiter, get_str) == 0)
	{
		*(hdoc_count) += 1;
		free(st->delimiter);
		free(get_str);
		return (NULL);
	}
	free(st->delimiter);
	if (get_str[0] == '\0')
		return (ft_strdup("\n"));
	return (ft_strjoin(get_str, "\n"));
}

static void	declare_var(int *total_hdoc, int *actual_hdoc, t_line *all_cmd)
{
	*total_hdoc = get_nbr_hdoc(all_cmd);
	*actual_hdoc = 0;
}

static void	heredoc_loop(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env)
{
	char	*global_var;
	int		temp_pipe[2];
	int		total_hdoc;
	int		actual_hdoc;

	pipe(temp_pipe);
	st->infile = temp_pipe[0];
	declare_var(&total_hdoc, &actual_hdoc, all_cmd);
	while (1)
	{
		st->tmp_str = heredoc_parsing(all_cmd, &actual_hdoc, st);
		if (actual_hdoc == total_hdoc || g_status == 130)
			break ;
		else
		{
			if (st->tmp_str)
			{
				global_var = replace_global_variable(st->tmp_str, main_env);
				write(temp_pipe[1], global_var, ft_strlen(global_var));
				free(global_var);
			}
		}
	}
	close(temp_pipe[1]);
}

int	check_hdoc(t_line *all_cmd)
{
	t_lst	*tmp;

	if (!all_cmd->infile || !lst_last(all_cmd->infile)->data)
		return (0);
	tmp = all_cmd->infile;
	while (tmp)
	{
		if (ft_strnstr(tmp->data, "<<", 2) != NULL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	heredoc(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env)
{
	if (check_hdoc(all_cmd) == 0)
		return (0);
	signal_handler();
	g_status = 254;
	heredoc_loop(st, all_cmd, main_env);
	if (st->tmp_str != NULL)
		free(st->tmp_str);
	if (g_status == 130)
		st->hdoc = 2;
	return (1);
}
