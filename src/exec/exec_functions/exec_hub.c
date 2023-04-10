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

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("CMD = %s\n", tab[i]);
		i++;
	}
}

static void	check_inout(t_env_pipe *st, t_line *all_cmd)
{
	if (all_cmd->infile != NULL)
		st->input = 1;
	else
		st->input = 0;
	if (all_cmd->outfile != NULL)
		st->output = 1;
	else
		st->output = 0;
}

static int	exec_cmd(int nb_cmd, char **cmd, \
	t_env_main *main_env, t_line *all_cmd)
{
	t_env_pipe	*st;

	st = malloc(sizeof(t_env_pipe));
	if (st == NULL)
		return (ft_printf("Error : %s\n", strerror(errno)));
	check_inout(st, all_cmd);
	if (!open_files(st, all_cmd))
		return (0);
	if (!set_up_struct(st, all_cmd, nb_cmd))
		return (0);
	if (!execution(cmd, main_env->env, st, main_env))
		return (0);
	return (1);
}

void	exec_hub(t_line *all_cmd, t_env_main *main_env)
{
	char	**cmd;

	cmd = cmd_to_send(all_cmd);
	if (!cmd)
		return ;
	if (exec_cmd(all_cmd->nbr_cmd, cmd, main_env, all_cmd))
		main_env->last_cmd_status = 0;
	else
		main_env->last_cmd_status = 1;
	free_str(cmd);
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
}
