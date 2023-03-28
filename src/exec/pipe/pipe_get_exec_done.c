/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_get_exec_done.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/28 14:07:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

int	find_path_index(char **env)
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

void	get_exec_done(char **argv, char **env, t_env_pipe *st)
{
	char	*path;
	int		path_pos_index;

	path = NULL;
	print_tab(argv);
	path_pos_index = find_path_index(env);
	if (path_pos_index == -1)
	{
		no_path(st, argv);
		return ;
	}
	if (env[path_pos_index])
		path = get_path(argv[0], env[path_pos_index], st);
	if (path == NULL)
		path_is_null(st, argv, argv);
	execve(path, argv, env);
	error_execve(argv, path, st);
}
