/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_files_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:44:34 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 09:26:09 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	special_case_redirect(t_line *all_cmd)
{
	char	*file_name;
	int		fd;

	if (ft_strnstr(all_cmd->outfile->data, ">", 1) != NULL)
	{
		file_name = setup_file(all_cmd->outfile->data);
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (0);
		free(file_name);
		close(fd);
	}
	return (1);
}

int	check_infile(t_line *all_cmd)
{
	char	*file_name;
	int		fd;

	if (ft_strnstr(all_cmd->infile->data, "<<", 2) != NULL)
		return (0);
	file_name = setup_file(all_cmd->infile->data);
	if (!file_name)
		return (0);
	fd = open(file_name, O_RDWR);
	if (fd == -1)
	{
		ft_printf(2, "%s: No such file or directory\n", file_name);
		free(file_name);
		return (0);
	}
	close(fd);
	free(file_name);
	if (ft_lstsize_file(all_cmd->outfile) == 1)
		special_case_redirect(all_cmd);
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
