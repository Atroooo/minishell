/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:32:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/13 16:52:25 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	print_list(t_env_var *env_list)
{
	if (!env_list)
		return ;
	while (env_list)
	{
		printf("declare -x ");
		if (env_list->name && env_list->value)
			printf("%s=%s\n", env_list->name, env_list->value);
		else if (env_list->name && !env_list->value)
			printf("%s=\n", env_list->name);
		env_list = env_list->next;
	}
}

static t_env_var	*add_env_value(char *str, t_env_var *env_list)
{
	char	*name;
	char	*value;
	int		in_env;

	in_env = check_if_in_env(env_list, str);
	if (set_variables_name_and_value(str, &name, &value))
		return (NULL);
	if ((str[0] == '$' && str[1] == '$') || (str[0] == '$' && in_env == 0))
	{
		ft_printf("bash: export: %s not a valid identifier\n");
		free_variable_name_and_value(name, value);
		return (env_list);
	}
	ft_lst_addback_env(&env_list, ft_lstnew_env(name, value));
	free_variable_name_and_value(name, value);
	return (env_list);
}

t_env_var	*ft_export(char **cmd, t_env_main *main_env)
{
	int	i;

	if (!cmd)
		return (NULL);
	if (ft_strcmp(cmd[0], "export") != 0)
		return (NULL);
	i = 1;
	if (!cmd[i])
	{
		print_list(main_env->env_list);
		main_env->last_cmd_status = 0;
		return (main_env->env_list);
	}
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
			main_env->env_list = add_env_value(cmd[i], main_env->env_list);
		else
			setenv(cmd[i], "", 1);
		i++;
	}
	main_env->last_cmd_status = 0;
	return (main_env->env_list);
}
