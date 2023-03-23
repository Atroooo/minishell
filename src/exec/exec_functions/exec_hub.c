/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 09:57:11 by marvin            #+#    #+#             */
/*   Updated: 2023/03/21 09:57:11 by marvin           ###   ########.fr       */
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
		ft_echo(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("env", cmd[0]) == 0)
		ft_env(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		ft_exit(cmd);
	else if (ft_strcmp("export", cmd[0]) == 0)
		main_env->env_list = ft_export(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		ft_pwd(cmd, main_env);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		main_env->env_list = ft_unset(cmd, main_env->env_list, main_env);
	else
		return (0);
	return (1);
}

static void	exec_single_cmd(char **cmd, char *env[], t_env_main *main_env)
{
	int	pid;

	if (buildin_exec(cmd, main_env))
	{
		main_env->last_cmd_status = 0;
		return ;
	}
	else if (cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (exec_cmd(cmd, env))
			{
				main_env->last_cmd_status = 0;
				return ;
			}
		}
	}
	main_env->last_cmd_status = 1;
}

void	exec_hub(t_line *all_cmd, char *env[], t_env_main *main_env)
{
	char	**strr;
	int		i;
	int		j;

	i = 0;
	if (all_cmd->nbr_cmd == 1)
	{
		if (all_cmd->all_cmd[0][0] && all_cmd->all_cmd[0][1] && all_cmd->all_cmd[0][2])
			printf("all_cmd->all_cmd[0][0] = %s\nall_cmd->all_cmd[0][1] = %s\nall_cmd->all_cmd[0][2] = %s\n", all_cmd->all_cmd[0][0], all_cmd->all_cmd[0][1], all_cmd->all_cmd[0][2]);
		exec_single_cmd(all_cmd->all_cmd[0], env, main_env);
		if (all_cmd->all_cmd)
			free_cmd(all_cmd);
	}
	else
	{
		 if (ft_strcmp(all_cmd->all_cmd[0][0], "exec") == 0)
		{
			strr = malloc(sizeof(char *) * 5);
			strr[0] = " ";
			strr[1] = "Makefile";
			strr[2] = "ls -la";
			strr[3] = "wc -l";
			strr[4] = "ls -la";
			strr[5] = "outfile";
			exec_pipe(6, strr, env, main_env);
		}
		while (all_cmd->all_cmd[i] != NULL)
		{
			j = 0;
			while (all_cmd->all_cmd[i][j] != NULL)
			{
				printf("all_cmd->all_cmd[%d][%d] = %s\n", i, j, all_cmd->all_cmd[i][j]);
				j++;
			}
			// printf("all_cmd->all_cmd[%d][0] = %s\n", i, all_cmd->all_cmd[i][0]);
			// if (ft_strcmp(all_cmd->all_cmd[i][0], "here_doc"))
			// 	exec_pipe(6, all_cmd->all_cmd[i], env, main_env);
			i++;
		}
	}
}