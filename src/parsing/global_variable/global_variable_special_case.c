/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable_special_case.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 08:37:42 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/13 18:16:22 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	check_if_not_between_quote(char before, char after)
{
	if (before == '\"' && after == '\"')
		return (1);
	return (0);
}

static int	interrogation_case(char **final_line, int lst_cmd_status)
{
	char	*nbr;
	int		size;

	nbr = ft_itoa(lst_cmd_status);
	if (nbr == NULL)
		return (INT_MIN);
	size = ft_strlen(nbr);
	ft_strlcpy(*final_line, nbr, size + 1);
	free(nbr);
	return (size);
}

static int	dollar_case(int *i_line)
{
	*i_line += 2;
	return (-2);
}

int	check_if_not_special_case(char *line, int *i_line, char *final_line, t_env_main *main_env)
{
	int	index;

	index = 0;
	if (*i_line > 0 && check_if_not_between_quote(line[*i_line - 1], line[*i_line + 1]))
		return (-2);
	else if (line[*i_line + 1] == '$')
		return (dollar_case(i_line));
	else if (line[*i_line + 1] == '?')
	{
		skip_gobal_variable(i_line, line);
		index = interrogation_case(&final_line, main_env->last_cmd_status);
		if (index < 0)
			return (-1);
	}
	return (index);
}
