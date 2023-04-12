/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 07:42:03 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/12 16:56:55 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	buildin_exec(char **cmd, t_env_main *main_env)
{
	if (!cmd)
		return (0);
	if (ft_strcmp("cd", cmd[0]) == 0)
		ft_cd(cmd, main_env);
	else if (ft_strcmp("echo", cmd[0]) == 0)
		ft_echo(cmd, main_env);
	else if (ft_strcmp("env", cmd[0]) == 0)
		ft_env(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		ft_exit(cmd, main_env);
	else if (ft_strcmp("export", cmd[0]) == 0)
		main_env->env_list = ft_export(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		ft_pwd(cmd, main_env);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		main_env->env_list = ft_unset(cmd, main_env->env_list, main_env);
	else
		return (0);
	if (main_env->env_list == NULL) /*Malloc a gerer*/
		return (-1);
	return (1);
}

static int	fork_declaration(char **cmd, char *env[], t_env_pipe *st, int i)
{
	st->pid[i] = fork();
	if (st->pid[i] < 0)
		return (quit_function(st, 1));
	if (st->pid[i] == 0)
	{
		if (!dup_manager(st))
			return (0);
		if (!get_exec_done(cmd[i], env, st))
			return (0);
	}
	return (1);
}

static void	wait_for_process(t_env_pipe *st)
{
	int	i;

	i = 0;
	while (i < st->nbr_cmd)
	{
		waitpid(st->pid[i], NULL, 0);
		i++;
	}
}

static void	end_the_progam(t_env_pipe *st)
{
	close_function(st);
	wait_for_process(st);
	free_pipe(st);
}

int	execution(char **cmd, char *env[], t_env_pipe *st, t_env_main *main_env)
{
	int	i;

	i = 0;
	if (buildin_exec(cmd, main_env))
	{
		quit_function(st, 2);
		return (1);
	}
	while (i < st->nbr_cmd)
	{
		if (!fork_declaration(cmd, env, st, i))
			return (0);
		st->actual_pipe += 1;
		i++;
	}
	end_the_progam(st);
	return (1);
}
