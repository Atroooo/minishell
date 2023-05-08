/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:09:04 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/08 11:01:27 by lcompieg         ###   ########.fr       */
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

static int	init_env_list(t_env_var **env_list, char **env)
{
	char		**env_split;
	t_env_var	*new_var;
	int			i;

	if (!env)
		exit(0);
	i = 0;
	while (env[i])
	{
		env_split = ft_split(env[i], '=');
		if (env_list == NULL)
			return (0);
		new_var = ft_lstnew_env(env_split[0], NULL);
		if (new_var == NULL)
			return (ft_free_tab(env_split), 0);
		if (size_tab(env_split) >= 2)
			new_var->value = ft_strdup(env[i] + ft_strlen(env_split[0]) + 1);
		if (!ft_lst_addback_env(env_list, new_var))
			return (ft_free_tab(env_split), -1);
		ft_free_tab(env_split);
		i++;
	}
	return (1);
}

static void	free_error_case(t_env_main *main_env)
{
	t_env_var	*tmp;

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
}

void	init_main_env(t_env_main *main_env, char **env)
{
	int	return_value;

	main_env->exit_status = 0;
	main_env->env_list = NULL;
	return_value = init_env_list(&main_env->env_list, env);
	if (return_value == 0)
		exit(-1);
	if (return_value == -1)
	{
		free_error_case(main_env);
		exit(-1);
	}
	termios_init(main_env);
}
