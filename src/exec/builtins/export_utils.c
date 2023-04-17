/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:54:14 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/17 13:23:53 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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

int	check_if_in_env(t_env_var *lst, char *str)
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
