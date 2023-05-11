/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:32 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/11 18:02:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	free_exit_builtin(t_env_main *main_env, t_line *all_cmd)
{
	if (main_env->env)
		free_str(main_env->env);
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
	reset_terminal(main_env);
	free_main_env(main_env);
}

static int	is_numeric(char *cmd)
{
	int	i;

	i = 1;
	if ((cmd[0] != '-' && cmd[0] != '+' && !ft_isdigit(cmd[0])) \
		|| ft_atoll(cmd) == -1)
		return (0);
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	special_case_exit(char **cmd, t_env_main *main_env, t_line *all_cmd)
{
	int	i;

	if (cmd_size(cmd) == 3)
	{
		i = 0;
		while (cmd[1][i])
		{
			if (ft_isdigit(cmd[1][i]))
				return (0);
			i++;
		}
		if (is_numeric(cmd[2]))
			free_exit_builtin(main_env, all_cmd);
		return (0);
	}
	return (0);	
}

static int	exit_one_cmd(char **cmd, t_env_main *main_env, t_line *all_cmd)
{
	if (cmd_size(cmd) == 2 && ft_strcmp(cmd[1], "-1") == 0)
	{
		g_status = (unsigned char)ft_atoll(cmd[1]);
		if (all_cmd->nbr_cmd == 1)
			free_exit_builtin(main_env, all_cmd);
	}
	if (!is_numeric(cmd[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		g_status = 2;
		return (1);
	}
	return (0);
}

void	ft_exit(char **cmd, t_env_main *main_env, t_line *all_cmd)
{
	special_case_exit(cmd, main_env, all_cmd);
	if (cmd_size(cmd) > 1)
	{
		if (exit_one_cmd(cmd, main_env, all_cmd))
			return ;
	}
	if (cmd_size(cmd) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_status = 1;
		return ;
	}
	else if (cmd[1])
		g_status = (unsigned char)ft_atoll(cmd[1]);
	if (all_cmd->nbr_cmd == 1)
		free_exit_builtin(main_env, all_cmd);
}
