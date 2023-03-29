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

//Segfault
void	free_all_exit(t_env_main *main_env)
{
	while (main_env->env_list)
	{
		if (main_env->env_list)
			free(main_env->env_list);
		main_env->env_list = main_env->env_list->next;
	}
	free_str(main_env->env);
	free(main_env->tty);
	exit(0);
}
