/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:26:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/10 14:36:31 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

static void	incr_shlvl(t_env_var *env_list)
{
	t_env_var	*tmp;
	int			lvl;

	if (env_list == NULL)
		return ;
	tmp = env_list;
	lvl = 0;
	while (ft_strcmp(tmp->name, "SHLVL") != 0)
		tmp = tmp->next;
	lvl = ft_atoi(tmp->value);
	if (lvl >= 999 || lvl < 0)
		lvl = 1;
	else
		lvl++;
	free(tmp->value);
	tmp->value = ft_itoa(lvl);
}

static int	init_env_list(t_env_var **env_list, char **env)
{
	char		**env_split;
	t_env_var	*new_var;
	int			i;

	i = 0;
	if (env[0] == NULL)
		return (1);
	while (env[i])
	{
		env_split = ft_split(env[i], '=');
		if (env_list == NULL)
			return (0);
		new_var = ft_lstnew_env(env_split[0], NULL);
		if (new_var == NULL)
			return (free_str(env_split), 0);
		if (size_tab(env_split) >= 2)
			new_var->value = ft_strdup(env[i] + ft_strlen(env_split[0]) + 1);
		*env_list = ft_lst_addsort(*env_list, new_var);
		free_str(env_split);
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

	g_status = 0;
	main_env->env_list = NULL;
	return_value = init_env_list(&main_env->env_list, env);
	if (return_value == 0)
		exit(-1);
	if (return_value == -1)
	{
		free_error_case(main_env);
		exit(-1);
	}
	incr_shlvl(main_env->env_list);
	termios_init(main_env);
}
