/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:14:38 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/28 12:08:37 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	copy_simple_quote(int *i_line, int *index, char *line, char *final_line)
{
	final_line[*index] = line[*i_line];
	*i_line += 1;
	*index += 1;
	while (line[*i_line] && line[*i_line] != '\'')
	{
		final_line[*index] = line[*i_line];
		*i_line += 1;
		*index += 1;
	}
}

t_env_var	*find_elem_in_list(char *name, t_env_var *env_list)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			break ;
		env_list = env_list->next;
	}
	return (env_list);
}

static int	copy_variable(char *line, int *index, t_env_var *env_list, char *final_line)
{
	char	*name;
	int		nbr_char;

	name = ft_substr(line, 0, count_alpha(line));
	if (name == NULL)
		return (-1);
	env_list = find_elem_in_list(name, env_list);
	free(name);
	if (env_list == NULL)
		return (0);
	nbr_char = ft_strlen(env_list->value);
	ft_strlcpy(final_line, env_list->value, nbr_char + 1);
	*index += nbr_char;
	return (0);
}

static int	check_if_quote(char c, int *del)
{
	if (c == '\"' && *del == 1)
	{
		*del = 0;
		return (0);
	}
	else if (c == '\"' && *del == 0)
	{
		*del = 1;
		return (0);
	}
	else if (c == '\'' && *del == 0)
		return (1);
	return (0);
}

static int	check_if_not_between_quote(char before, char after)
{
	if (!(before == '\"' && after == '\"'))
		return (1);
	return (0);
}

int	get_global_variable(char *line, char *final_line, \
						int *i_line, t_env_var *env_list)
{
	int	index;

	index = 0;
	if (check_if_not_between_quote(line[*i_line - 1], line[*i_line + 1]))
	{
		if (copy_variable(&line[*i_line + 1], &index, env_list, &final_line[0]))
			return (INT_MIN);
		skip_gobal_variable(i_line, line);
	}
	return (index);
}

int	get_final_line(char *line, t_env_var *env_list, char *final_line)
{
	int		i_line;
	int		index;
	int		del;

	del = 0;
	i_line = 0;
	index = 0;
	while (line[i_line])
	{
		if (check_if_quote(line[i_line], &del))
			copy_simple_quote(&i_line, &index, line, final_line);
		if (line[i_line] == '$')
		{
			index += get_global_variable(&line[0], &final_line[index], &i_line, env_list);
			if (index < 0)
				return (-1);
		}
		final_line[index] = line[i_line];
		incrementation(&i_line, &index, line[i_line]);
	}
	final_line[index] = '\0';
	return (0);
}

char	*replace_global_variable(char *line, t_env_var *env_list)
{
	char	*final_line;

	final_line = malloc(sizeof(char) * (count_nbr_char(line, env_list) + 1));
	if (final_line == NULL)
		return (NULL);
	if (get_final_line(line, env_list, &final_line[0]))
		return (NULL);
	return (final_line);
}
