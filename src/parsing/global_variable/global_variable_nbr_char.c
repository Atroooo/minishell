/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable_nbr_char.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:35:09 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/27 10:32:06 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	check_if_not_between_quote(char before, char after)
{
	if (before == '\"' && after == '\"')
		return (1);
	return (0);
}

static int	special_case_count(char *line, int *index, int *nbr_char)
{
	if (*index > 0 && check_if_not_between_quote(line[*index - 1], line[*index + 1]))
		return (1);
	else if (line[*index + 1] == '?')
	{
		*nbr_char += 3;
		return (1);
	}
	else if (ft_isalnum(line[*index + 1]) == 0)
		return (1);
	return (0);
}

static int	get_global_variable(char *line, int *nbr_char, t_env_var *env_list)
{
	char	*name;

	name = ft_substr(line, 0, count_alpha(line));
	if (name == NULL)
		return (-1);
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			break ;
		env_list = env_list->next;
	}
	free(name);
	if (env_list == NULL)
		return (0);
	*nbr_char += ft_strlen(env_list->value);
	return (0);
}

int	count_nbr_char(char *line, t_env_var *env_list)
{
	int	index;
	int	nbr_char;

	index = 0;
	nbr_char = 0;
	while (line[index])
	{
		if (line[index] == '\'')
			skip_simple_quote(&index, &nbr_char, line);
		while (line[index] == '$')
		{
			if (special_case_count(line, &index, &nbr_char) == 0)
				if (get_global_variable(&line[index + 1], &nbr_char, env_list))
					return (-1);
			skip_gobal_variable(&index, line);
		}
		incrementation(&index, &nbr_char, line[index]);
	}
	return (nbr_char + 1);
}
