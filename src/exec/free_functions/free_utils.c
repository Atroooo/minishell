/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:23:53 by marvin            #+#    #+#             */
/*   Updated: 2023/03/21 15:23:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	free_str(char **str)
{
	int	index;

	index = 0;
	if (!str)
		return ;
	while (str[index])
	{
		if (str[index])
			free(str[index]);
		index++;
	}
	free(str);
}

void	free_cmd(t_line *all_cmd)
{
	int	index;

	index = 0;
	while (all_cmd->all_cmd[index])
	{
		free_str(all_cmd->all_cmd[index]);
		index++;
	}
	free(all_cmd->all_cmd);
}

void	free_inout_list(t_lst *lst)
{
	t_lst	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->data)
			free(lst->data);
		free(lst);
		lst = tmp;
	}
}

void	free_cmd_exec(t_line *all_cmd, t_env_pipe *st, t_env_main *main_env)
{
	if (main_env->env)
		free_str(main_env->env);
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
	quit_function(st, 2);
	free_main_env(main_env);
}

void	free_main_env(t_env_main *main_env)
{
	t_env_var	*tmp;

	rl_clear_history();
	while (main_env->env_list)
	{
		tmp = main_env->env_list->next;
		if (main_env->env_list->name != NULL)
			free(main_env->env_list->name);
		if (main_env->env_list->value != NULL)
			free(main_env->env_list->value);
		if (main_env->env_list != NULL)
			free(main_env->env_list);
		main_env->env_list = tmp;
	}
	exit(g_status);
}
