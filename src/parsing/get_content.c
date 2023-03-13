/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:35:38 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/13 17:45:30 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_len_content(char *line, int count_content)
{
	int		i;
	int		y;
	char	selector;

	i = 0;
	y = skip_space(line);
	if (line[y] == '\'')
	{
		selector = '\'';
		y++;
	}
	else if (line[y] == '\"')
	{
		selector = '\"';
		y++;
	}
	else
		selector = ' ';
	while (line[y + i] != selector && line[y + i] != '\0')
		i++;
	if (count_content)
		return (i + y);
	if (line[i])
		return (i + 1);
	return (i);
}

static int	count_content(char *line)
{
	int		content_nbr;
	int		i;
	int		temp;

	content_nbr = 0;
	temp = get_len_content(line, 1);
	i = temp;
	while (temp > 0)
	{
		temp = get_len_content(&line[i], 1);
		i += temp;
		if (line[i])
			i += 1;
		content_nbr += 1;
	}
	return (content_nbr);
}

int	copy_content(char *line, char *content)
{
	int	i;
	int	y;
	int	size;
	int	del;

	del = 0;
	i = skip_space(line);
	size = get_len_content(line, 0);
	if (line[i] == '\'' || line[i] == '\"')
	{
		del = 1;
		size -= 1;
		i += 1;
	}
	y = 0;
	while (y < size)
	{
		content[y] = line[i];
		i++;
		y++;
	}
	content[y] = '\0';//changer ca
	if (del == 1)
		i += 1;
	return (i);
}

int	copy_all_content(char *line, t_cmd *cmd, int nbr_content)
{
	int	line_index;
	int	content_index;

	line_index = 0;
	content_index = 0;
	while (content_index < nbr_content)
	{
		cmd->content[content_index] = malloc(sizeof(char) * get_len_content(&line[line_index], 0) + 1);
		if (cmd->content == NULL)
			exit (1);
		line_index += copy_content(&line[line_index], cmd->content[content_index]);
		content_index += 1;
	}
	cmd->content[content_index] = NULL;
	return (line_index);
}

int	get_content(char *line, t_cmd *cmd)
{
	int	line_index;
	int	nbr_content;

	if (line[0] == 0)
		return (0);
	nbr_content = count_content(line);
	if (nbr_content == 0)
		return (0);
	cmd->content = malloc(sizeof(char *) * nbr_content + 1);
	if (cmd->content == NULL)
		exit (1); //A GERER PLUS TARD
	line_index = copy_all_content(line, cmd, nbr_content);
	return (line_index);
}
