/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_get_exec_done.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/29 17:27:45 by lcompieg         ###   ########.fr       */
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

static char	**get_cmd_hdoc(char **argv)
{
	char	**cmd;
	int		i;
	int		j;

	cmd = malloc(sizeof(char *) * (cmd_size(argv) + 1));
	if (!cmd)
		return (NULL);
	i = 1;
	j = 0;
	while (argv[i])
	{
		cmd[j] = ft_strdup(argv[i]);
		if (!cmd[j])
			return (NULL);
		i++;
		j++;
	}
	cmd[j] = NULL;
	return (cmd);
}

static int	get_index(t_env_pipe *st)
{
	int	i;

	if (st->infile != 0 && st->outfile != 1)
		i = 2;
	else if (st->infile != 0 || st->outfile != 1)
		i = 1;
	else
		i = 0;
	return (i);
}

static char	**parse_cmd(char **cmd, t_env_pipe *st)
{
	char	**s_cmd;
	int		i;
	int		j;

	if (!cmd)
		return (NULL);
	i = get_index(st);
	s_cmd = malloc(sizeof(char *) * (cmd_size(cmd) - i + 1));
	if (!s_cmd)
		return (NULL);
	j = 0;
	while (cmd[i])
	{
		s_cmd[j] = ft_strdup(cmd[i]);
		if (!s_cmd[j])
			return (NULL);
		i++;
		j++;
	}
	s_cmd[j] = NULL;
	return (s_cmd);
}

void	get_exec_done(char **argv, char **env, t_env_pipe *st)
{
	char	**cmd;
	char	*path;
	int		path_pos_index;

	path = NULL;
	path_pos_index = find_path_index(env);
	if (st->hdoc == 1)
		cmd = get_cmd_hdoc(argv);
	else if (st->infile != 0 && st->outfile == 1)
		cmd = argv;
	else
		cmd = parse_cmd(argv, st);
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