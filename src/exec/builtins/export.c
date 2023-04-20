/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:32:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/20 16:22:18 by vgonnot          ###   ########.fr       */
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
		if (env_list->name && env_list->value && env_list->value[0] != 0)
			printf("%s=\"%s\"\n", env_list->name, env_list->value);
		else
			printf("%s\n", env_list->name);
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

static int	check_export_error(char *cmd) //ERREUR AVEC $?
{
	if (cmd[0] == '$' || cmd[0] == '#')
		return (0);
	if (ft_isalpha(cmd[0]) == 0)
	{
		printf("export: `%c': not a valid identifier\n", cmd[0]);
		return (1);
	}
	return (0);
}

t_env_var	*ft_export(char **cmd, t_env_main *main_env)
{
	int	i;

	if (!cmd)
		return (NULL);
	if (ft_strcmp(cmd[0], "export") != 0)
		return (NULL);
	i = 1;
	if (cmd[1] == NULL)
	{
		print_list(main_env->env_list);
		return (main_env->env_list);
	}
	while (cmd[i])
	{
		if (check_export_error(cmd[i]))
			return (main_env->env_list);
		main_env->env_list = add_env_value(cmd[i], main_env->env_list);
		i++;
	}
	return (main_env->env_list);
}
