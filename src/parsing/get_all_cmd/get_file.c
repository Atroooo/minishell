/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:29:57 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/03 15:12:54 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += skip_in_between(&line[i], line[i]);
		if (line[i])
			i++;
	}
	return (i);
}

int	get_file(char *line, t_cmd *cmd, int index)
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
		error = lst_add_back(&cmd->infile, lst_new_index(file_str, index));
	else
		error = lst_add_back(&cmd->outfile, lst_new_index(file_str, index));
	if (error)
		return (-1);
	return (size);
}

int	get_element_file(int *i, char *line, t_cmd *cmd, int index)
{
	int	temp;

	temp = get_file(line, cmd, index);
	if (temp == -1)
		return (-1);
	*i += temp;
	return (0);
}
