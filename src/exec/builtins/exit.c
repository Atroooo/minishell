/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:32 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/19 15:26:35 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	free_exit_builtin(t_env_main *main_env, t_line *all_cmd)
{
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
	free_main_env(main_env);
}

void	ft_exit(char **cmd, t_env_main *main_env, t_line *all_cmd)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "exit") != 0)
		return ;
	if (cmd_size(cmd) > 1)
	{
		if ((cmd[1][0] != '-' && cmd[1][0] != '+' && !ft_isdigit(cmd[1][0])) \
			|| !ft_atoi(cmd[1]))
		{
			ft_printf("exit: %s: numeric argument required\n", cmd[1]);
			main_env->last_cmd_status = 2;
			return ;
		}
	}
	if (cmd_size(cmd) > 2)
	{
		ft_printf("exit: too many arguments\n");
		main_env->last_cmd_status = 1;
		return ;
	}
	else
		main_env->last_cmd_status = ft_atoi(cmd[1]);
	free_exit_builtin(main_env, all_cmd);
}
