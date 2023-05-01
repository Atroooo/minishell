/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_files_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:44:34 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/01 15:28:01 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	check_inout(t_env_pipe *st, t_line *all_cmd)
{
	if (all_cmd->infile != NULL)
		st->input = 1;
	else
		st->input = 0;
	if (all_cmd->outfile != NULL && \
		lst_last(all_cmd->outfile)->index == all_cmd->nbr_cmd - 1)
		st->output = 1;
	else
		st->output = 0;
}

int	check_infile(t_line *all_cmd)
{
	char	*file_name;
	int		fd;

	file_name = setup_file(all_cmd->infile->data);
	if (!file_name)
		return (0);
	fd = open(file_name, O_RDWR);
	if (fd == -1)
	{
		ft_putstr_fd(file_name, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free(file_name);
		return (0);
	}
	close(fd);
	free(file_name);
	return (1);
}

int	check_spe_outfile(t_env_pipe *st, t_line *all_cmd)
{
	t_lst	*tmp;

	tmp = all_cmd->outfile;
	while (tmp)
	{
		if (tmp->index == st->i)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	open_outfile(t_env_pipe *st, t_line *all_cmd)
{
	t_lst	*tmp;

	tmp = all_cmd->outfile;
	while (tmp)
	{
		if (tmp->index == st->i)
		{
			if (!setup_outfile(st, tmp->data))
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	create_outfiles(t_line *all_cmd)
{
	t_lst	*tmp_outfile;
	char	*file_name;
	int		c_outfile;

	tmp_outfile = all_cmd->outfile;
	while (tmp_outfile != NULL)
	{
		if (all_cmd->infile && \
			tmp_outfile->index_inline > all_cmd->infile->index_inline)
			break ;
		file_name = setup_file(tmp_outfile->data);
		if (ft_strnstr(tmp_outfile->data, ">>", 2) != NULL)
			c_outfile = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (ft_strnstr(tmp_outfile->data, ">", 1) != NULL)
			c_outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (c_outfile == -1)
			return (0);
		close(c_outfile);
		free(file_name);
		tmp_outfile = tmp_outfile->next;
	}
	return (1);
}
