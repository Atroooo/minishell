/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:17:52 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/10 08:04:23 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	setup_pipe(t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		st->fd[i] = malloc(sizeof(int) * 2);
		if (st->fd[i] == NULL || pipe(st->fd[i]) == -1)
		{
			free_env(st, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	print_err_msg(t_line *all_cmd)
{
	char	*file_name;

	ft_putstr_fd("Cannot open file : ", STDERR_FILENO);
	file_name = setup_file(lst_last(all_cmd->infile)->data);
	if (!file_name)
		return (0);
	ft_putendl_fd(file_name, STDERR_FILENO);
	free(file_name);
	return (0);
}

int	setup_struct_cmd(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env)
{
	st->nbr_cmd = all_cmd->nbr_cmd;
	st->hdoc = heredoc(st, all_cmd, main_env);
	if (st->hdoc == -1)
		return (0);
	if (st->hdoc == 1 && st->error_msg == -1)
		return (print_err_msg(all_cmd));
	st->error_msg = 0;
	st->actual_pipe = 0;
	st->pid = malloc(sizeof(int) * (st->nbr_cmd + 1));
	if (st->pid == NULL)
	{
		free_env(st, -1);
		return (0);
	}
	st->fd = malloc(sizeof(int *) * (st->nbr_cmd));
	if (st->fd == NULL)
	{
		free(st->pid);
		free_env(st, -1);
		return (0);
	}
	if (!setup_pipe(st))
		return (0);
	return (1);
}
