/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:32:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/27 07:51:42 by vgonnot          ###   ########.fr       */
=======
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:32:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/27 13:11:14 by lcompieg         ###   ########.fr       */
>>>>>>> lucas
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	print_list(t_env_var *env_list)
{
	if (!env_list)
		return ;
	while (env_list)
	{
		if (env_list->name && env_list->value)
			ft_printf("%s=%s\n", env_list->name, env_list->value);
		else if (env_list->name && !env_list->value)
			ft_printf("%s=\n", env_list->name);
		env_list = env_list->next;
	}
}

static int	ft_intchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	check_if_in_env(t_env_var *lst, char *str)
{
	char	*name;

	name = ft_substr(str, 0, ft_intchr(str, '='));
	if (name == NULL)
		return (-1);
	while (lst != NULL)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			free(name);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static void	free_variable_name_and_value(char *name, char *value)
{
	if (name)
		free(name);
	if (value)
		free(value);
}

static int	set_variables_name_and_value(char *str, char **name, char **value)
{
	int	dollars;

	dollars = 0;
	if (str[0] == '$')
		dollars = 1;
	*name = ft_substr(str, 0, ft_intchr(str, '=') - dollars);
	*value = ft_substr(str, ft_intchr(str, '=') + 1, ft_strlen(str));
	if (name == NULL || value == NULL)
	{
		free_variable_name_and_value(*name, *value);
		return (-1);
	}
	return (0);
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

t_env_var	*ft_export(char **cmd, t_env_var *env_list, t_env_main *main_env)
{
	int	i;

	if (!cmd)
		return (NULL);
	if (ft_strcmp(cmd[0], "export") != 0)
		return (NULL);
	i = 1;
	if (!cmd[i])
	{
		print_list(env_list);
		main_env->last_cmd_status = 0;
		return (env_list);
	}
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
			env_list = add_env_value(cmd[i], env_list);
		else
			setenv(cmd[i], "", 1);
		i++;
	}
	main_env->last_cmd_status = 0;
	return (env_list);
}
