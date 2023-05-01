/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/01 10:33:10 by lcompieg         ###   ########.fr       */
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
	{
		cmd = ft_env(cmd, main_env);
		if (main_env->exit_status == 2)
			return (main_env->exit_status = 0, 0);
	}
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

static void	print_msg(t_env_main *main_env, char **cmd, t_env_pipe *st)
{
	ft_putstr_fd(cmd[0], 2);
	if (ft_strncmp(cmd[0], "./", 2) == 0)
	{
		ft_putendl_fd(": Permission denied", 2);
		main_env->exit_status = 126;
	}
	else if (st->error_msg == 1)
	{
		ft_putendl_fd(": No such file or directory", 2);
		main_env->exit_status = 1;
	}
	else
	{
		ft_putendl_fd(": command not found", 2);
		main_env->exit_status = 127;
	}
}

int	get_exec_done(t_line *all_cmd, char **cmd, \
	t_env_pipe *st, t_env_main *main_env)
{
	char	*path;

	path = NULL;
	if (buildin_exec(cmd, main_env))
	{
		close(0);
		close(1);
		close_function(st);
		free_cmd_exec(all_cmd, st, main_env);
	}
	path = set_path(main_env->env, cmd, st);
	if (path == NULL)
	{
		close(0);
		close(1);
		print_msg(main_env, cmd, st);
		free_cmd_exec(all_cmd, st, main_env);
		return (0);
	}
	execve(path, cmd, main_env->env);
	return (0);
}
