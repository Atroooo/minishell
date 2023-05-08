/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable_utils_bis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:27:24 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/08 15:40:41 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	not_between_quote(char *line, int i_line)
{
	if (i_line < 1)
		return (1);
	if (line[i_line - 1] == '"' && line[i_line + 1] == '"')
		return (0);
	if (line[i_line - 1] == '\'' && line[i_line + 1] == '\'')
		return (0);
	return (1);
}

int	check_if_need_to_skip_global_variable(char *line, int *i_line)
{
	if (line[*i_line + 1] == ' ' || line[*i_line + 1] == '\0' \
	|| ft_isalnum(line[*i_line + 1]) == 0)
		if (line[*i_line + 1] != '*' && line[*i_line + 1] != '"' \
			&& line[*i_line + 1] != '\'' \
			&& line[*i_line + 1] != '?')
			return (1);
	return (0);
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

static int	copy_variable(char *line, int *index, \
	t_env_var *env_list, char *final_line)
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

int	get_gbl_var(char *line, char *final_line, \
						int *i_line, t_env_main *main_env)
{
	int	index;
	int	temp;

	index = 0;
	temp = check_if_not_special_case(line, i_line, \
		&final_line[index]);
	if (temp == -1)
		return (INT_MIN);
	if (temp > 0)
		index += temp;
	if (temp == 0)
	{
		if (copy_variable(&line[*i_line + 1], &index, \
				main_env->env_list, &final_line[0]))
			return (INT_MIN);
		skip_gobal_variable(i_line, line);
	}
	return (index);
}
