/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable_nbr_char.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:35:09 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/28 11:37:04 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	get_global_variable(char *line, int *nbr_char, t_env_var *env_list)
{
	char	*name;

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
		if (line[index] == '$')
		{
			get_global_variable(&line[index + 1], &nbr_char, env_list);
			skip_gobal_variable(&index, line);
		}
		incrementation(&index, &nbr_char, line[index]);
	}
	return (nbr_char);
}
