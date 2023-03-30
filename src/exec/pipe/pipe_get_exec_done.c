/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_get_exec_done.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/30 18:04:34 by lcompieg         ###   ########.fr       */
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
/*Envoyer cmd une par une du con*/
void	get_exec_done(char **argv, char **env, t_env_pipe *st)
{
	char	**cmd;
	char	*path;
	int		path_pos_index;

	path = NULL;
	path_pos_index = find_path_index(env);
	cmd = argv;
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
	error_execve(argv, path, st);
}
