/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:14:38 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/19 15:32:37 by lcompieg         ###   ########.fr       */
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
	int	len_name;
	int	len_env;

	len_name = ft_strlen(name);
	while (env_list != NULL)
	{
		len_env = ft_strlen(env_list->name);
		if (len_name > len_env)
		{
			if (ft_strncmp(env_list->name, name, len_name) == 0)
				break ;
		}
		else
			if (ft_strncmp(env_list->name, name, len_env) == 0)
				break ;
		env_list = env_list->next;
	}
	return (env_list);
}

static int	copy_variable(char *line, int *index, t_env_var *env_list, char *final_line)
{
	char	*name;
	int		nbr_char;

	if (ft_isdigit(line[0]) || line[0] == '*')
		name = ft_substr(line, 0, 1);
	else
		name = ft_substr(line, 0, count_alpha(line));
	if (name == NULL)
		return (-1);
	env_list = find_elem_in_list(name, env_list);
	free(name);
	if (env_list == NULL)
	{
		return (0);
	}
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

int	get_gbl_var(char *line, char *final_line, \
						int *i_line, t_env_main *main_env)
{
	int	index;
	int	temp;

	index = 0;
	temp = check_if_not_special_case(line, i_line, &final_line[index], main_env);
	if (temp == -1)
		return (INT_MIN);
	if (temp > 0)
		index += temp;
	if (temp == 0)
	{
		if (copy_variable(&line[*i_line + 1], &index, main_env->env_list, &final_line[0]))
			return (INT_MIN);
		skip_gobal_variable(i_line, line);
	}
	return (index);
}

int	gbl_var_check(char *line, char *final_line, \
						int *i_line, t_env_main *main_env)
{
	int	index;

	index = 0;
	while (line[*i_line] == '$')
	{
		if (line[*i_line + 1] == ' ' || line[*i_line + 1] == '\0' || ft_isalnum(line[*i_line + 1]) == 0)
			if (line[*i_line + 1] != '*' && line[*i_line + 1] != '"' && line[*i_line + 1] != '\'')
				return (index);
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
	final_line = malloc(sizeof(char) * (len + 1));
	if (final_line == NULL)
		return (NULL);
	if (get_final_line(line, main_env, &final_line[0]))
	{
		free(final_line);
		free(line);
		return (NULL);
	}
	return (final_line);
}
