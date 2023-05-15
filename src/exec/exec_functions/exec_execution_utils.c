/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/15 13:30:12 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	buildin_exec(char **cmd, t_env_main *main_env, \
	t_env_pipe *st, t_line *all_cmd)
{
	if (ft_strcmp("cd", cmd[0]) == 0)
		main_env->env_list = ft_cd(cmd, main_env->env_list);
	else if (ft_strcmp("echo", cmd[0]) == 0)
		ft_echo(cmd, st);
	else if (ft_strcmp("env", cmd[0]) == 0)
	{
		cmd = ft_env(cmd, main_env);
		if (g_status == 2)
			return (g_status = 0, 0);
	}
	else if (ft_strcmp("exit", cmd[0]) == 0)
		ft_exit(cmd, main_env, all_cmd);
	else if (ft_strcmp("export", cmd[0]) == 0)
		main_env->env_list = ft_export(cmd, main_env);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		ft_pwd(cmd, st);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		main_env->env_list = ft_unset(cmd, main_env->env_list);
	else
		return (0);
	if (main_env->env_list == NULL)
		return (-1);
	return (1);
}

static void	print_msg(char **cmd, t_env_pipe *st)
{
	if (st->hdoc == 1)
		return ;
	if (cmd[0] == NULL)
		return ;
	ft_putstr_fd(cmd[0], 2);
	if (cmd && ft_strncmp(cmd[0], "./", 2) == 0)
	{
		ft_putendl_fd(": Permission denied", 2);
		g_status = 126;
	}
	else if (st->error_msg == 1)
	{
		ft_putendl_fd(": No such file or directory", 2);
		g_status = 1;
	}
	else
	{
		ft_putendl_fd(": command not found", 2);
		g_status = 127;
	}
}

int	is_executable(char **cmd)
{
	if (cmd[0] == NULL)
		return (0);
	if (cmd[0][0] == '\0')
		return (0);
	return (1);
}

static void	close_zero_one(void)
{
	close(0);
	close(1);
}

int	get_exec_done(t_line *all_cmd, char **cmd, \
	t_env_pipe *st, t_env_main *main_env)
{
	char	*path;

	path = NULL;
	if (is_executable(cmd) == 1)
	{
		if (buildin_exec(cmd, main_env, st, all_cmd))
		{
			close_zero_one();
			close_function(st);
			free_cmd_exec(all_cmd, st, main_env);
		}
	}
	path = return_path(main_env->env, cmd, st);
	if (path == NULL)
	{
		close_zero_one();
		print_msg(cmd, st);
		free_cmd_exec(all_cmd, st, main_env);
		return (0);
	}
	close_function(st);
	activate_sig();
	execve(path, cmd, main_env->env);
	return (0);
}
