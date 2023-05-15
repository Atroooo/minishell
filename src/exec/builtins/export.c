/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:32:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 08:21:45 by vgonnot          ###   ########.fr       */
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
		free_variable_name_and_value(name, value);
		return (env_list);
	}
	if (in_env == 1 && value != NULL && value[0] != '\0')
		env_list = remove_similar_variable(name, env_list);
	else if (in_env == 1)
	{
		free_variable_name_and_value(name, value);
		return (env_list);
	}
	env_list = ft_lst_addsort(env_list, ft_lstnew_env(name, value));
	free_variable_name_and_value(name, value);
	return (env_list);
}

static void	print_export_error(char *cmd, int s)
{
	g_status = 1;
	if (s == 0)
	{
		ft_printf(2, "export: `%s': not a valid identifier\n", cmd);
		return ;
	}
	if (s == 1)
	{
		ft_printf(2, "%s: evnet not found", cmd);
		return ;
	}
}

static int	check_export_error(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '-')
		return (print_export_error(cmd, 0), 1);
	if (ft_isdigit(cmd[0]) || cmd[0] == '=' || cmd[0] == '\0')
		return (print_export_error(cmd, 0), 1);
	while (cmd[i] != '\0' && cmd[i] != '=')
	{	
		if (cmd[i] == '!')
			return (print_export_error(&cmd[i], 1), 1);
		if (cmd[i] == '@' || cmd[i] == '%' || cmd[i] == '?' \
		|| cmd[i] == '*' || cmd[i] == '\\' || cmd[i] == '~' \
		|| cmd[i] == '-' || cmd[i] == '.' || cmd[i] == '{' \
		|| cmd[i] == '}' || cmd[i] == '#' || cmd[i] == '+')
			return (print_export_error(cmd, 0), 1);
		i++;
	}
	while (cmd[i])
	{
		if (cmd[i] == '!')
			return (print_export_error(&cmd[i], 1), 1);
		i++;
	}
	return (0);
}

t_env_var	*ft_export(char **cmd, t_env_main *main_env)
{
	int	i;

	if (!cmd)
		return (NULL);
	i = 1;
	if (cmd[1] == NULL)
	{
		print_list(main_env->env_list);
		return (main_env->env_list);
	}
	while (cmd[i])
	{
		if (check_export_error(cmd[i]) == 0)
			main_env->env_list = add_env_value(cmd[i], main_env->env_list);
		i++;
	}
	return (main_env->env_list);
}
