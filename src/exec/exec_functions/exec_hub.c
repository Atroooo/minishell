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
	if (!all_cmd->all_cmd[0] || !all_cmd->all_cmd[0][0] \
		|| all_cmd->all_cmd[0][0][0] == '\0')
		return (0);
	if (ft_strcmp("exit", all_cmd->all_cmd[0][0]) == 0)
		ft_exit(all_cmd->all_cmd[0], main_env, all_cmd);
	else if (all_cmd->outfile == NULL && \
	ft_strcmp("export", all_cmd->all_cmd[0][0]) == 0)
		main_env->env_list = ft_export(all_cmd->all_cmd[0], main_env);
	else if (ft_strcmp("unset", all_cmd->all_cmd[0][0]) == 0)
		main_env->env_list = ft_unset(all_cmd->all_cmd[0], \
			main_env->env_list);
	else if (ft_strcmp("cd", all_cmd->all_cmd[0][0]) == 0)
		main_env->env_list = ft_cd(all_cmd->all_cmd[0], main_env->env_list);
	else
		return (0);
	if (main_env->env_list == NULL)
		return (-1);
	return (1);
}

static int	check_inout(t_env_pipe *st, t_line *all_cmd)
{
	st->hdoc = check_hdoc(all_cmd);
	if (all_cmd->infile != NULL)
		st->input = 1;
	else
		st->input = 0;
	if ((all_cmd->outfile != NULL && \
		lst_last(all_cmd->outfile)->index == all_cmd->nbr_cmd -1) || \
		(all_cmd->nbr_cmd > 1 && all_cmd->all_cmd[0][0] == NULL))
		st->output = 1;
	else
		st->output = 0;
	if (!open_files(st, all_cmd))
		return (0);
	return (1);
}

static int	exec_cmd(t_env_main *main_env, t_line *all_cmd)
{
	t_env_pipe	*st;

	if (!env_lst_to_char(main_env))
		return (-1);
	if (all_cmd->nbr_cmd == 1)
		if (buildin_exec(all_cmd, main_env))
			return (1);
	st = malloc(sizeof(t_env_pipe));
	if (st == NULL)
	{
		ft_putstr_fd("Error : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	st->error_msg = 0;
	if (!check_inout(st, all_cmd))
		return (0);
	if (!setup_struct_cmd(st, all_cmd, main_env))
		return (-1);
	if (!execution(all_cmd, st, main_env))
	{
		free_cmd_exec(all_cmd, st, main_env);
		return (0);
	}
	return (1);
}

static void	redirection_hub(t_line *all_cmd)
{
	if (ft_lstsize_file(all_cmd->outfile) > 0)
	{
		if (!create_outfiles(all_cmd))
			return ;
	}
	if (all_cmd->infile && all_cmd->all_cmd[0][0] == NULL)
		check_infile(all_cmd);
}

void	exec_hub(t_line *all_cmd, t_env_main *main_env)
{
	redirection_hub(all_cmd);
	if ((all_cmd->all_cmd[0][0] != NULL && all_cmd->nbr_cmd > 0) \
		|| all_cmd->nbr_cmd > 1 || check_hdoc(all_cmd) == 1)
	{
		if (exec_cmd(main_env, all_cmd) == -1)
		{
			if (main_env->env)
				free_str(main_env->env);
			free_cmd(all_cmd);
			free_inout_list(all_cmd->infile);
			free_inout_list(all_cmd->outfile);
			reset_terminal(main_env);
			free_main_env(main_env);
			return ;
		}
		free_str(main_env->env);
	}
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
}
