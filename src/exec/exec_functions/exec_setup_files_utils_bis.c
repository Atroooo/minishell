/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_files_utils_bis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:12:51 by atro              #+#    #+#             */
/*   Updated: 2023/05/18 19:09:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	check_file_status_redir(char *file_name)
{
	struct stat	info;
	int			file_status;

	file_status = lstat(file_name, &info);
	if (file_status == 0 && S_ISDIR(info.st_mode))
	{
		ft_putstr_fd(file_name, 2);
		ft_putendl_fd(": Is a directory", 2);
		free(file_name);
		return (0);
	}
	if (file_status == 0 && !S_IRWXU)
	{
		g_status = 1;
		ft_putstr_fd(file_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		free(file_name);
		return (0);
	}
	return (1);
}

int	check_file_status_exec(char *file_name, t_env_pipe *st, t_line *all_cmd)
{
	struct stat	info;
	int			file_status;

	file_status = lstat(file_name, &info);
	if (file_status == 0 && (S_ISDIR(info.st_mode) || !S_IRWXU))
	{
		free(file_name);
		if (all_cmd->nbr_cmd == 1)
			free(st);
		return (0);
	}
	return (1);
}

int	check_spe_infile(t_env_pipe *st, t_line *all_cmd)
{
	t_lst	*tmp;

	if (all_cmd->infile == NULL)
		return (0);
	tmp = all_cmd->infile;
	while (tmp)
	{
		if (tmp->index == st->i)
		{
			if (ft_strnstr(tmp->data, "<<", 2) != NULL)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_spe_outfile(t_env_pipe *st, t_line *all_cmd)
{
	t_lst	*tmp;

	if (all_cmd->outfile == NULL)
		return (0);
	tmp = all_cmd->outfile;
	while (tmp)
	{
		if (tmp->index == st->i)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
