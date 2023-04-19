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

static int	buildin_exec(t_line *all_cmd, t_env_main *main_env)
{
	if (!all_cmd->all_cmd[0])
		return (0);
	if (ft_strcmp("exit", all_cmd->all_cmd[0][0]) == 0)
		ft_exit(all_cmd->all_cmd[0], main_env, all_cmd);
	else if (all_cmd->outfile == NULL && \
	ft_strcmp("export", all_cmd->all_cmd[0][0]) == 0)
		main_env->env_list = ft_export(all_cmd->all_cmd[0], main_env);
	else if (ft_strcmp("unset", all_cmd->all_cmd[0][0]) == 0)
		main_env->env_list = ft_unset(all_cmd->all_cmd[0], \
			main_env->env_list, main_env);
	else
		return (0);
	if (main_env->env_list == NULL)
		return (-1);
	return (1);
}

static void	check_inout(t_env_pipe *st, t_line *all_cmd)
{
	if (all_cmd->infile != NULL)
		st->input = 1;
	else
		st->input = 0;
	if (all_cmd->outfile != NULL && \
		lst_last(all_cmd->outfile)->index == all_cmd->nbr_cmd - 1)
		st->output = 1;
	else
		st->output = 0;
}

static int	exec_cmd(t_env_main *main_env, t_line *all_cmd)
{
	t_env_pipe	*st;

	if (all_cmd->nbr_cmd == 1)
	{
		if (buildin_exec(all_cmd, main_env))
			return (1);
	}
	st = malloc(sizeof(t_env_pipe));
	if (st == NULL)
		return (ft_printf("Error : %s\n", strerror(errno)));
	check_inout(st, all_cmd);
	if (!open_files(st, all_cmd))
		return (0);
	if (!setup_struct_cmd(st, all_cmd, main_env))
		return (0);
	if (!execution(all_cmd, st, main_env))
	{
		free_cmd_exec(all_cmd, st, main_env);
		return (0);
	}
	return (1);
}

void	exec_hub(t_line *all_cmd, t_env_main *main_env)
{
	if (exec_cmd(main_env, all_cmd))
		main_env->exit_status = 0;
	else
		main_env->exit_status = 1;
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
}
