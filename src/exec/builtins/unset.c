/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:31 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 13:43:29 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	check_unset_error(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '-')
		return (print_unset_error(cmd, 0), 1);
	if (ft_isdigit(cmd[0]) || cmd[0] == '=' || cmd[0] == '\0')
		return (print_unset_error(cmd, 0), 1);
	while (cmd[i] != '\0')
	{	
		if (cmd[i] == '!')
			return (print_unset_error(&cmd[i], 1), 1);
		if (cmd[i] == '@' || cmd[i] == '%' || cmd[i] == '?' \
		|| cmd[i] == '*' || cmd[i] == '\\' || cmd[i] == '~' \
		|| cmd[i] == '-' || cmd[i] == '.' || cmd[i] == '{' \
		|| cmd[i] == '}' || cmd[i] == '#' || cmd[i] == '+' \
		|| cmd[i] == '=' || cmd[i] == '^')
			return (print_unset_error(cmd, 0), 1);
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

static void	free_node(t_env_var *delete)
{
	free(delete->name);
	free(delete->value);
	free(delete);
}

static t_env_var	*delete_node(t_env_var *env_list, int i)
{
	t_env_var	*temp;
	t_env_var	*delete;
	t_env_var	*prev;

	temp = env_list;
	if (i == 0)
	{
		delete = env_list;
		env_list = env_list->next;
		free_node(delete);
		return (env_list);
	}
	else
	{
		prev = get_prev(env_list, i - 1);
		if (!prev->next)
			return (temp);
		delete = prev->next;
		prev->next = delete->next;
		free_node(delete);
		delete = NULL;
		return (temp);
	}
}

static t_env_var	*find_in_list(char *name, t_env_var *env_list)
{
	t_env_var	*temp;
	int			i;

	if (!name || !env_list)
		return (env_list);
	temp = env_list;
	i = 0;
	while (temp)
	{
		if (temp && temp->name && ft_strcmp(temp->name, name) == 0)
		{
			env_list = delete_node(env_list, i);
			g_status = 0;
			return (env_list);
		}
		i++;
		temp = temp->next;
	}
	return (env_list);
}

t_env_var	*ft_unset(char **cmd, t_env_var *env_list)
{
	int	i;

	if (!cmd)
		return (env_list);
	i = 1;
	while (cmd[i])
	{
		if (check_unset_error(cmd[i]) == 0)
			env_list = find_in_list(cmd[i], env_list);
		i++;
	}
	return (env_list);
}
