/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/17 15:16:36 by atro             ###   ########.fr       */
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

static int	buildin_exec(char **cmd, t_env_main *main_env)
{
	if (!cmd)
		return (0);
	if (ft_strcmp("cd", cmd[0]) == 0)
		ft_cd(cmd, main_env);
	else if (ft_strcmp("echo", cmd[0]) == 0)
		ft_echo(cmd, main_env);
	else if (ft_strcmp("env", cmd[0]) == 0)
		ft_env(cmd, main_env);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("export", cmd[0]) == 0)
		main_env->env_list = ft_export(cmd, main_env);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		ft_pwd(cmd, main_env);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		main_env->env_list = ft_unset(cmd, main_env->env_list, main_env);
	else
		return (0);
	if (main_env->env_list == NULL)
		return (-1);
	return (1);
}

static char	*set_path(char **env, char **cmd, t_env_pipe *st)
{
	char	*path;
	int		path_pos_index;

	path_pos_index = find_path_index(env);
	if (path_pos_index == -1)
	{
		no_path(st, cmd);
		return (NULL);
	}
	if (env[path_pos_index])
	{
		path = get_path(cmd[0], env[path_pos_index]);
		return (path);
	}
	return (NULL);
}

int	get_exec_done(t_line *all_cmd, char **cmd, \
	t_env_pipe *st, t_env_main *main_env)
{
	char	*path;

	path = NULL;
	if (buildin_exec(cmd, main_env))
	{
		free_cmd(all_cmd);
		free_inout_list(all_cmd->infile);
		free_inout_list(all_cmd->outfile);
		quit_function(st, 2);
		free_all_exit(main_env);
		exit(1);
	}
	if (!cmd)
		return (quit_function(st, 1));
	path = set_path(main_env->env, cmd, st);
	if (path == NULL)
	{
		path_is_null(st, cmd, cmd[0]);
		return (0);
	}
	execve(path, cmd, main_env->env);
	error_execve(cmd, path, st);
	return (0);
}
