/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:14:38 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/08 15:40:54 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	copy_simple_quote(int *i_line, int *index, \
	char *line, char *final_line)
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

int	gbl_var_check(char *line, char *final_line, \
						int *i_line, t_env_main *main_env)
{
	int	index;

	index = 0;
	while (line[*i_line] == '$' && not_between_quote(line, *i_line))
	{
		if (check_if_need_to_skip_global_variable(line, i_line))
			return (0);
		index += get_gbl_var(&line[0], &final_line[index], i_line, main_env);
		if (index < 0)
			return (INT_MIN);
	}
	return (index);
}

int	get_final_line(char *line, t_env_main *main_env, char *final_line)
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
		index += gbl_var_check(&line[0], &final_line[index], &i_line, main_env);
		if (index < 0)
			return (-1);
		final_line[index] = line[i_line];
		incrementation(&i_line, &index, line[i_line]);
	}
	final_line[index] = '\0';
	return (0);
}

char	*replace_global_variable(char *line, t_env_main *main_env)
{
	char	*final_line;	
	int		len;

	len = count_nbr_char(line, main_env->env_list);
	if (len == -1)
		return (NULL);
	final_line = malloc(sizeof(char) * (len + 1));
	if (final_line == NULL)
		return (NULL);
	if (get_final_line(line, main_env, &final_line[0]))
	{
		free(final_line);
		free(line);
		return (NULL);
	}
	free(line);
	return (final_line);
}
