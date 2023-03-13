/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_done.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/13 12:50:21 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	**get_arg_vec(t_env *st, char **argv)
{
	char	**arg_vec;

	arg_vec = ft_split(argv[st->actual_pipe + 2 + st->hdoc], ' ');
	if (arg_vec == NULL)
		quit_function(st, -1);
	return (arg_vec);
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

void	get_exec_done(char **argv, char **env, t_env *st)
{
	char	**arg_vec;
	char	*path;
	int		path_pos_index;

	arg_vec = get_arg_vec(st, argv);
	path_pos_index = find_path_index(env);
	if (path_pos_index == -1)
	{
		no_path(st, arg_vec);
		return ;
	}
	if (env[path_pos_index])
		path = get_path(arg_vec[0], env[path_pos_index], st);
	if (path == NULL)
		path_is_null(st, arg_vec, argv);
	execve(path, arg_vec, env);
	error_execve(arg_vec, path, st);
}
