/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:28:02 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/27 14:49:28 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

// static int	redirect_input(char **cmd, int *pipe_fd, t_env_main *main_env)
// {
// 	char	*file;
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (ft_strncmp(cmd[i], "<", 1) == 0)
// 		{
// 			file = setup_file(cmd[i]);
// 			fd = open(file, O_RDONLY, 0777);
// 			if (fd == -1)
// 			{
// 				ft_printf("minishell: %s: No such file or directory\n");
// 				return (0);
// 			}
// 			dup2(fd, 0);
// 			dup2(pipe_fd[1], 1);
// 			close(pipe_fd[0]);
// 			main_env->input = fd;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// static int	redirect_output(char **cmd, int *pipe_fd, t_env_main *main_env)
// {
// 	char	*file;
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (ft_strncmp(cmd[i], ">", 1) == 0)
// 		{
// 			file = setup_file(cmd[i]);
// 			fd = open(file, O_WRONLY, 0777);
// 			if (fd == -1)
// 			{
// 				ft_printf("minishell: %s: No such file or directory\n");
// 				return (0);
// 			}
// 			dup2(fd, 1);
// 			dup2(pipe_fd[0], 0);
// 			close(pipe_fd[1]);
// 			main_env->output = fd;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

static int	redirect_output_append(char **cmd, int *pipe_fd, \
	t_env_main *main_env)
{
	char	*file;
	int		fd;
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], ">>", 2) == 0)
		{
			file = setup_file(cmd[i]);
			fd = open(file, O_APPEND, 0777);
			if (fd == -1)
			{
				ft_printf("minishell: %s: No such file or directory\n");
				return (0);
			}
			dup2(fd, 1);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[1]);
			main_env->output = fd;
			return (1);
		}
		i++;
	}
	return (1);
}

int	redirect_hub(t_line *all_cmd, t_env_main *main_env)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (0);
	if (all_cmd->nbr_cmd == 1)
	{
		// if (!redirect_input(all_cmd->all_cmd[0], pipe_fd, main_env))
		// 	return (0);
		// if (!redirect_output(all_cmd->all_cmd[0], pipe_fd, main_env))
		// 	return (0);
		if (!redirect_output_append(all_cmd->all_cmd[0], pipe_fd, main_env))
			return (0);
	}
	return (1);
}
