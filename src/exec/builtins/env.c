/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:30 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/09 19:25:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	print_list(t_env_var *env_list)
{
	if (!env_list)
		return ;
	while (env_list)
	{
		if (env_list->name && env_list->value && env_list->value[0] != 0)
			printf("%s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
}

char	**ft_env(char **cmd, t_env_main *main_env)
{
	int	i;

	i = 1;
	if (!cmd)
		return (cmd);
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "env"))
		{
			g_status = 2;
			return (&cmd[i]);
		}
		i++;
	}
	print_list(main_env->env_list);
	g_status = 0;
	return (cmd);
}
