/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/10 14:19:41 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	find_path_index(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strstart(env[i], "PATH="))
			return (i);
		i++;
	}
	return (-1);
}

int	get_exec_done(char *cmd, char **env, t_env_pipe *st)
{
	char	**cmd_s;
	char	*path;
	int		path_pos_index;

	path = NULL;
	path_pos_index = find_path_index(env);
	cmd_s = ft_split(cmd, ' ');
	if (!cmd_s)
		return (quit_function(st, 1));
	if (path_pos_index == -1)
	{
		no_path(st, cmd_s);
		return (0);
	}
	if (env[path_pos_index])
		path = get_path(cmd_s[0], env[path_pos_index]);
	if (path == NULL)
	{
		path_is_null(st, cmd_s, cmd);
		return (0);
	}
	execve(path, cmd_s, env);
	error_execve(cmd_s, path, st);
	return (0);
}
