/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:22:07 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/08 09:51:21 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	count_split(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	get_element(int *i, \
			int (*get)(char *, t_cmd *), char *line, t_cmd *cmd)
{
	int	temp;

	temp = get(line, cmd);
	if (temp == -1)
		return (-1);
	*i += temp;
	return (0);
}

static void	set_up_newlst(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->flag = NULL;
	cmd->content = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
}

int	initialize_variable( \
			t_cmd *cmd, int *error, int *no_command, int *is_echo)
{
	*no_command = TRUE;
	*is_echo = FALSE;
	*error = 0;
	set_up_newlst(cmd);
	return (0);
}

int	check_if_get_cmd(char c, int *no_command, int error)
{
	if (c != '\0' && *no_command == TRUE && error == 0)
	{
		*no_command = FALSE;
		return (1);
	}
	return (0);
}
