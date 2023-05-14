/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_files_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:44:34 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/14 15:09:27 by atro             ###   ########.fr       */
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
		perror(file_name);
		free(file_name);
		return (0);
	}
	close(fd);
	free(file_name);
	if (ft_lstsize_file(all_cmd->outfile) == 1)
		special_case_redirect(all_cmd);
	return (1);
}

int	setup_spe_infile(t_env_pipe *st, t_line *all_cmd)
{
	t_lst	*tmp;
	char	*file_name;

	tmp = all_cmd->infile;
	while (tmp)
	{
		if (tmp->index == st->i)
		{
			if (ft_strnstr(tmp->data, "<<", 2) != NULL)
				return (0);
			file_name = setup_file(tmp->data);
			if (!file_name)
				return (0);
			st->infile = open(file_name, O_RDWR);
			if (st->infile == -1)
			{
				perror(file_name);
				free(file_name);
				return (0);
			}
			free(file_name);
			return (1);
		}
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
			if (!setup_outfile(st, tmp->data, all_cmd))
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	create_outfiles(t_line *all_cmd)
{
	t_lst		*tmp;
	char		*file_name;
	int			c_outfile;

	tmp = all_cmd->outfile;
	while (tmp != NULL)
	{
		if (all_cmd->infile && tmp->idx_line > all_cmd->infile->idx_line)
			break ;
		file_name = setup_file(tmp->data);
		if (!file_name)
			return (0);
		if (!check_file_status_redir(file_name))
			break ;
		if (ft_strnstr(tmp->data, ">>", 2) != NULL)
			c_outfile = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (ft_strnstr(tmp->data, ">", 1) != NULL)
			c_outfile = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (c_outfile == -1)
			return (0);
		close(c_outfile);
		free(file_name);
		tmp = tmp->next;
	}
	return (1);
}
