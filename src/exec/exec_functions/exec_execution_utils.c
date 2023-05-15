/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execution_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:31:08 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/15 16:29:54 by lcompieg         ###   ########.fr       */
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
	if (cmd && ft_strncmp(cmd[0], "./", 2) == 0 && st->error_msg != 2)
	{
		ft_printf(2, "%s: Permission Denied\n", cmd[0]);
		g_status = 126;
	}
	else if (st->error_msg == 1)
	{
		ft_printf(2, "%s: No such file or directory\n", cmd[0]);
		g_status = 1;
	}
	else if (st->error_msg == 2)
	{
		ft_printf(2, "%s: is a directory\n", cmd[0]);
		g_status = 126;
	}
	else
	{
		ft_printf(2, "%s: Command not found\n", cmd[0]);
		g_status = 127;
	}
}

static void	special_case_global_var(char **cmd, char *path)
{
	if (access(cmd[0], X_OK) != -1)
		ft_printf(2, "%s: Is a directory\n", cmd[0]);
	if (path)
		free(path);
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
	special_case_global_var(cmd, path);
	return (0);
}
