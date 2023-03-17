/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:32:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/16 20:04:46 by marvin           ###   ########.fr       */
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

static t_env_var	*add_env_value(char *str, t_env_var *env_list)
{
	char	*name;
	char	*value;

	if (str[0] == '$' && str[1] == '$')
	{
		ft_printf("bash: %s not a valid identifier\n");
		return (env_list);
	}
	if (str[0] == '$')
	{
		name = ft_substr(str, 1, ft_intchr(str, '=') - 1);
		value = ft_substr(str, ft_intchr(str, '=') + 1, ft_strlen(str));
	}
	else
	{
		name = ft_substr(str, 0, ft_intchr(str, '='));
		value = ft_substr(str, ft_intchr(str, '=') + 1, ft_strlen(str));
	}
	ft_lst_addback_env(&env_list, ft_lstnew_env(name, value));
	free(name);
	free(value);
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