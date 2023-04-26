/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:31 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/26 16:11:16 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	check_unset_error(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '-')
		return (printf("export: `-%c': not a valid identifier\n", cmd[1]));
	if (ft_isdigit(cmd[0]) || cmd[0] == '=' || cmd[0] == '\0')
		return (printf("export: `%s': not a valid identifier\n", cmd));
	while (cmd[i] != '\0')
	{	
		if (cmd[i] == '!')
			return (printf("%s: event not found\n", &cmd[i]));
		if (cmd[i] == '@' || cmd[i] == '%' || cmd[i] == '?' \
		|| cmd[i] == '*' || cmd[i] == '\\' || cmd[i] == '~' \
		|| cmd[i] == '-' || cmd[i] == '.' || cmd[i] == '{' \
		|| cmd[i] == '}' || cmd[i] == '#' || cmd[i] == '+' \
		|| cmd[i] == '=' || cmd[i] == '^')
			return (printf("export: `%s': not a valid identifier\n", cmd));
		i++;
	}
	return (0);
}

static t_env_var	*get_prev(t_env_var *env_list, int i)
{
	t_env_var	*prev;
	int			j;

	j = 0;
	prev = env_list;
	while (j < i)
	{
		if (!prev->next)
			return (NULL);
		prev = prev->next;
		j++;
	}
	return (prev);
}

static void	delete_node(t_env_var *env_list, int i)
{
	t_env_var	*delete;
	t_env_var	*prev;

	if (i == 0)
	{
		delete = env_list;
		env_list = env_list->next;
		free(delete->name);
		free(delete->value);
		free(delete);
		return ;
	}
	else
	{
		prev = get_prev(env_list, i - 1);
		if (!prev->next)
			return ;
		delete = prev->next;
		prev->next = delete->next;
		free(delete->name);
		free(delete->value);
		free(delete);
	}
}

static void	find_in_list(char *name, t_env_var *env_list, t_env_main *main_env)
{
	t_env_var	*temp;
	int			i;

	if (!name || !env_list)
		return ;
	temp = env_list;
	i = 0;
	while (temp)
	{
		if (temp && temp->name && ft_strcmp(temp->name, name) == 0)
		{
			delete_node(env_list, i);
			main_env->exit_status = 0;
			return ;
		}
		i++;
		temp = temp->next;
	}
}

t_env_var	*ft_unset(char **cmd, t_env_var *env_list, t_env_main *main_env)
{
	int	i;

	if (!cmd)
		return (env_list);
	if (ft_strcmp(cmd[0], "unset") != 0)
		return (env_list);
	i = 1;
	while (cmd[i])
	{
		if (check_unset_error(cmd[i]) == 0)
			find_in_list(cmd[i], env_list, main_env);
		i++;
	}
	return (env_list);
}
