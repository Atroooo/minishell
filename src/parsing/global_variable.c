/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:14:38 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/27 18:10:13 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

static int	get_global_variable(char *line, int *index, t_env_var *env_list, char **final_line)
{
	char	*name;
	int		nbr_char;

	name = ft_substr(line, 0, count_alpha(line));
	if (name == NULL)
		exit (1);//A GERER PLUS TARD;
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			break ;
		env_list = env_list->next;
	}
	free(name);
	if (env_list == NULL)
		return (0);
	nbr_char = ft_strlen(env_list->value);
	ft_strlcpy(*final_line, env_list->value, nbr_char);
	*index += nbr_char;
	return (0);
}

char	*get_final_line(char *line, t_env_var *env_list)
{
	int		i_line;
	int		index;
	char	*final_line;

	final_line = malloc(sizeof(char) * (count_nbr_char(line, env_list) + 2));
	if (final_line == NULL)
		return (NULL);
	i_line = 0;
	index = 0;
	while (line[i_line])
	{
		if (line[i_line] == '\'')
			copy_simple_quote(&i_line, &index, line, final_line);
		if (line[i_line] == '$')
		{
			if (get_global_variable(&line[index + 1], &index, env_list, &final_line)) //A MODIFIER MARCHE PAS
				return (NULL);
			skip_gobal_variable(&i_line, line);
		}
		final_line[index] = line[i_line];
		incrementation(&i_line, &index, line[i_line]);
	}
	final_line[index] = '\0';
	return (final_line);
}

char	*replace_global_variable(char *line, t_env_var *env_list)
{
	char	*final_line;

	final_line = get_final_line(line, env_list);
	return (final_line);
}
