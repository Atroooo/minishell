/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:28:02 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/23 13:09:26 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	redirect_input(char **cmd, int *pipe_fd, t_env_main *main_env)
{
	int	fd;
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0)
		{
			if (cmd[i + 1] == NULL)
				return ;
			fd = open(cmd[i] + 1, O_RDONLY, 0777);
			if (fd == -1)
				return ;
			dup2(fd, 0);
			dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
			main_env->input = fd;
		}
		i++;
	}
}

static void	redirect_output(char **cmd, int *pipe_fd, t_env_main *main_env)
{
	int	fd;
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">") == 0)
		{
			if (cmd[i + 1] == NULL)
				return ;
			fd = open(cmd[i] + 1, O_WRONLY, 0777);
			if (fd == -1)
				return ;
			dup2(fd, 1);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[1]);
			main_env->output = fd;
		}
		i++;
	}
}

static void	redirect_output_append(char **cmd, int *pipe_fd, \
	t_env_main *main_env)
{
	int	fd;
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">>") == 0)
		{
			if (cmd[i + 1] == NULL)
				return ;
			fd = open(cmd[i] + 1, O_APPEND, 0777);
			if (fd == -1)
				return ;
			dup2(fd, 1);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[1]);
			main_env->output = fd;
		}
		i++;
	}
}

void	redirect_hub(t_line *all_cmd, t_env_main *main_env)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	if (all_cmd->nbr_cmd == 1)
	{
		redirect_input(all_cmd->all_cmd[0], pipe_fd, main_env);
		redirect_output(all_cmd->all_cmd[0], pipe_fd, main_env);
		redirect_output_append(all_cmd->all_cmd[0], pipe_fd, main_env);
	}
}
