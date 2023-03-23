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
		ft_exit(cmd, main_env);
	else if (ft_strcmp("export", cmd[0]) == 0)
		main_env->env_list = ft_export(cmd, main_env->env_list, main_env);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		ft_pwd(cmd, main_env);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		main_env->env_list = ft_unset(cmd, main_env->env_list, main_env);
	else
		return (0);
	main_env->last_cmd_status = 0;
	return (1);
}

static char	**sgl_cmd_to_send(char **cmd, t_env_main *main_env)
{
	char	**s_cmd;
	int		i;
	int		j;

	s_cmd = malloc(sizeof(char) * cmd_size(cmd));
	if (main_env->input != 0 && main_env->output != 1)
		i = 2;
	else if (main_env->input != 0 || main_env->output != 1)
		i = 1;
	else
		i = 0;
	j = 0;
	while (cmd[i])
	{
		s_cmd[j] = ft_strdup(cmd[i]);
		i++;
		j++;
	}
	s_cmd[j] = NULL;
	return (s_cmd);
}

static char	**cmd_to_send(t_line *all_cmd)
{
	char	**s_cmd;
	int		i;
	int		j;
	int		k;

	s_cmd = malloc(sizeof(char) * (get_total_cmd(all_cmd) + 1));
	if (!s_cmd)
		return (NULL);
	i = 0;
	while (all_cmd->all_cmd[i])
	{
		j = 0;
		while (all_cmd->all_cmd[i][j])
		{
			printf("oui\n");
			s_cmd[k] = ft_strdup(all_cmd->all_cmd[i][j]);
			j++;
			k++;
		}
		i++;
	}
	s_cmd[k] = NULL;
	return (s_cmd);
}

static void	exec_single_cmd(char **cmd, t_env_main *main_env)
{
	char	**s_cmd;

	s_cmd = sgl_cmd_to_send(cmd, main_env);
	if (buildin_exec(s_cmd, main_env))
		return ;
	else if (s_cmd != NULL)
		exec_pipe(cmd_size(s_cmd), s_cmd, main_env);
	free_str(s_cmd);
}

void	exec_hub(t_line *all_cmd, t_env_main *main_env)
{
	if (all_cmd->nbr_cmd == 1)
	{
		if (redirect_hub(all_cmd, main_env))
			exec_single_cmd(all_cmd->all_cmd[0], main_env);
		if (all_cmd->all_cmd)
			free_cmd(all_cmd);
	}
	else
		exec_pipe(get_total_cmd(all_cmd), cmd_to_send(all_cmd), \
			main_env);
}
