/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:55:29 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/11 17:31:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	join_path(char **path_split, char *cmd, int index)
{
	char	*temp;

	if (index == 0)
		temp = ft_strjoin(&path_split[0][5], "/");
	else
		temp = ft_strjoin(path_split[index], "/");
	if (temp == NULL)
		return (0);
	free(path_split[index]);
	path_split[index] = ft_strjoin(temp, cmd);
	if (path_split[index] == NULL)
		return (0);
	free(temp);
	return (1);
}

static void	set_path(char **path_split, char *cmd)
{
	int		index;

	index = 0;
	while (path_split[index])
	{
		if (!join_path(path_split, cmd, index))
			return ;
		index++;
	}
}

static char	*check_if_cmd_exist(char **path_split, char *temp)
{
	int		ac;
	int		i;

	ac = -1;
	i = 0;
	while (ac == -1 && path_split[i])
		ac = access(path_split[i++], X_OK);
	if (ac != -1)
	{
		temp = ft_strjoin(temp, path_split[i -1]);
		ft_free_2d_array(path_split);
		return (temp);
	}
	ft_free_2d_array(path_split);
	return (NULL);
}

static char	*get_path(char *cmd, char *paths)
{
	char	**path_split;
	char	*temp;

	temp = NULL;
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) != -1)
		return (ft_strjoin(temp, cmd));
	path_split = ft_split(paths, ':');
	if (path_split == NULL)
		return (NULL);
	set_path(path_split, cmd);
	return (check_if_cmd_exist(path_split, temp));
}

char	*return_path(char **env, char **cmd, t_env_pipe *st)
{
	char	*path;
	int		path_pos_index;

	if (is_executable(cmd) == 0)
		return (NULL);
	if (cmd[0][0] != '.' && cmd[0][1] != '/' && ft_strchr(cmd[0], '/'))
		return (ft_strdup(cmd[0]));
	path_pos_index = find_path_index(env);
	if (path_pos_index == -1)
	{
		st->error_msg = 1;
		return (NULL);
	}
	if (env[path_pos_index])
	{
		path = get_path(cmd[0], env[path_pos_index]);
		return (path);
	}
	return (NULL);
}
