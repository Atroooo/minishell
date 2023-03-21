/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:15:29 by marvin            #+#    #+#             */
/*   Updated: 2023/03/21 15:15:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*get_env(char **env)
{
	int		i;
	int		j;
	char	*substr;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		substr = ft_substr(env[i], 0, j);
		if (ft_strncmp(substr, "PATH", ft_strlen(substr)) == 0)
		{
			free(substr);
			return (env[i] + j + 1);
		}
		free(substr);
		i++;
	}
	return (NULL);
}

static char	*get_path_single(char *cmd, char **env)
{
	int		index;
	char	*exec;
	char	**all_path;
	char	*path_part;
	char	**cmd_s;

	index = 0;
	all_path = ft_split(get_env(env), ':');
	cmd_s = ft_split(cmd, ' ');
	while (all_path[index])
	{
		path_part = ft_strjoin(all_path[index], "/");
		exec = ft_strjoin(path_part, cmd_s[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_str(cmd_s);
			return (exec);
		}
		free(exec);
		index++;
	}
	free_str(all_path);
	free_str(cmd_s);
	return (cmd);
}

int	exec_cmd(char **cmd, char **env)
{
	char	*path;

    // dup2(fd, 1);
	// dup2(p_fd[0], 0);
	path = get_path_single(cmd[0], env);
	if (execve(path, cmd, env) == -1)
	{
		ft_printf("minishell: command not found: %s", cmd[0]);
		// free_str(cmd_s);
		return (0);
	}
	return (1);
}
