/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:30 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/19 18:07:49 by vgonnot          ###   ########.fr       */
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

void	ft_env(char **cmd, t_env_main *main_env)
{
	int	i;

	i = 1;
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "env") != 0)
		return ;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "env"))
		{
			return ; //RETURN UN TABLEAU 2D EN RETIRANT TOUT LES ENV EX [ENV ENV LS -L] return [LS -L]
		}
		i++;
	}
	print_list(main_env->env_list);
	main_env->exit_status = 0;
}
