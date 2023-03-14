/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:31 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 13:06:25 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	delete_var(t_env_var *env_list, t_env_var *prev, t_env_var *next)
{
	if (prev)
		prev->next = next;
	if (env_list->name)
		free(env_list->name);
	if (env_list->value)
		free(env_list->value);
	free(env_list);
}

static void	find_in_list(char *name, t_env_var *env_list, t_env_main *main_env)
{
	t_env_var	*temp;

	if (!name || !env_list)
		return ;
	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			temp->name = NULL;
			temp->value = NULL;
			main_env->last_cmd_status = 0;
		}
		temp = temp->next;
	}
}

void	ft_unset(char **cmd, t_env_var *env_list, t_env_main *main_env)
{
	int	i;

	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "unset") != 0)
		return ;
	i = 1;
	while (cmd[i])
	{
		find_in_list(cmd[i], env_list, main_env);
		i++;
	}
}
