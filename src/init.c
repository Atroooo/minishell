/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:09:04 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 12:22:03 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	init_env_list(t_env_var **env_list)
{
	char	**env;
	int		i;

	env = ft_split(getenv("PATH"), ':');
	if (!env)
		exit(0);
	i = 0;
	while (env[i])
	{
		*env_list = add_env_value(env[i], *env_list);
		i++;
	}
}

void	init_main_env(t_env_main *main_env)
{
	main_env->env_list = malloc(sizeof(t_env_var));
	if (!main_env->env_list)
	{
		free(main_env);
		exit(0);
	}
	init_env_list(&main_env->env_list);
}
