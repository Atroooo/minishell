/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:09:04 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/16 22:11:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	size_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

static void	init_env_list(t_env_var **env_list, char **env)
{
	char		**env_split;
	t_env_var	*new_var;
	int		i;

	if (!env)
		exit(0);
	i = 0;
	while (env[i])
	{
		env_split = ft_split(env[i], '=');
		if (env_list == NULL)
			return ;
		new_var = ft_lstnew_env(env_split[0], NULL);
		if (new_var == NULL)
			return ;
		if (size_tab(env_split) >= 2)
			new_var->value = ft_strdup(env[i] + ft_strlen(env_split[0]) + 1);
		ft_lst_addback_env(env_list, new_var);
		ft_free_tab(env_split);
		i++;
	}
}

void	init_main_env(t_env_main *main_env, char **env)
{
	main_env->env_list = malloc(sizeof(t_env_var));
	if (!main_env->env_list)
	{
		free(main_env);
		exit(0);
	}
	init_env_list(&main_env->env_list, env);
	termios_init(main_env);
}
