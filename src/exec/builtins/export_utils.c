/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:54:14 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/03 16:20:54 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	get_index_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	check_if_in_env(t_env_var *lst, char *str)
{
	char	*name;

	name = ft_substr(str, 0, get_index_char(str, '='));
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
	free(name);
	return (0);
}

void	free_variable_name_and_value(char *name, char *value)
{
	if (name)
		free(name);
	if (value)
		free(value);
}

int	set_variables_name_and_value(char *str, char **name, char **value)
{
	int	dollars;
	int	position_equal;

	dollars = 0;
	position_equal = get_index_char(str, '=');
	if (str[0] == '$')
		dollars = 1;
	*name = ft_substr(str, 0, position_equal - dollars);
	*value = ft_substr(str, position_equal + 1, ft_strlen(str));
	if (*name == NULL || *value == NULL)
	{
		free_variable_name_and_value(*name, *value);
		return (-1);
	}
	
	return (0);
}
