/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:29:57 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/10 13:29:45 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	skip_char(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == c)
		i++;
	return (i);
}

static int	get_size_file(char *line)
{
	int	i;

	i = skip_char(line, line[0]);
	i += skip_space(&line[i]);
	while (line[i] && line[i] != ' ')
		i++;
	return (i);
}

int	get_file(char *line, t_cmd *cmd)
{
	int		size;
	char	*file_str;
	int		error;

	size = get_size_file(line);
	file_str = malloc(sizeof(char) * (size + 1));
	if (file_str == NULL)
		return (-1);
	file_str = copy_cmd(size, line, file_str);
	if (file_str[0] == '<')
		error = lst_add_back(&cmd->infile, lst_new(file_str));
	else
		error = lst_add_back(&cmd->outfile, lst_new(file_str));
	if (error)
		return (-1);
	return (size);
}
