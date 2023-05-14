/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_files_utils_bis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:12:51 by atro              #+#    #+#             */
/*   Updated: 2023/05/14 13:54:04 by atro             ###   ########.fr       */
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
	if (file_status == 0 && S_IRWXU)
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
	if (file_status == 0 && (S_ISDIR(info.st_mode) || S_IRWXU))
	{
		free(file_name);
		if (all_cmd->nbr_cmd == 1)
			free(st);
		return (0);
	}
	return (1);
}
