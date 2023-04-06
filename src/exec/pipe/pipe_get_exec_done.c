/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_get_exec_done.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/06 22:48:24 by marvin           ###   ########.fr       */
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

void	get_exec_done(char *argv, char **env, t_env_pipe *st)
{
	char	**cmd;
	char	*path;
	int		path_pos_index;

	path = NULL;
	path_pos_index = find_path_index(env);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		return ;
	print_tab(cmd);
	if (path_pos_index == -1)
	{
		no_path(st, cmd);
		return ;
	}
	if (env[path_pos_index])
		path = get_path(cmd[0], env[path_pos_index], st);
	if (path == NULL)
		path_is_null(st, cmd, argv);
	execve(path, cmd, env);
	error_execve(cmd, path, st);
}
