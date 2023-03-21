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

#include "../../header/minishell.h"

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

void	exec_cmd(t_line *all_cmd, char *env[], t_env_main *main_env)
{
	int		i;

	i = 0;
    while (all_cmd->all_cmd[i] != NULL)
	{
		buildin_exec(all_cmd->all_cmd[i], main_env);
		// redirect_input(all_cmd->all_cmd[i]);
		// redirect_output(all_cmd->all_cmd[i]);
		// redirect_output_append(all_cmd->all_cmd[i]);
		if (ft_strcmp(all_cmd->all_cmd[i][0], "here_doc"))
			exec_pipe(6, all_cmd->all_cmd[i], env, main_env);
		i++;
	}
}
