/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:35:38 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/11 21:40:31 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	count_content(char *line)
{
	int		i;
	int		content_nbr;
	char	quote;

	i = 0;
	content_nbr = 0;
	quote = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && quote == 0)
		{
			content_nbr += 1;
			i += skip_space(&line[i]);
			if ((line[i] == '\'' || line[i] == '\"') && quote == 0)
			{
				quote = line[i];
				i++;
			}
		}
		if (quote != 0 && quote == line[i])
		{
			quote = 0;
		}
		if (line[i] != '\0')
			i++;
	}
	return (content_nbr);
}

int	get_len_content(char *line) //NE MARCHE PO
{
	int		i;
	char	selector;

	i = 0;
	selector = line[i];
	if (selector == ' ')
		i += skip_space(line);
	while (line[i] != selector)
		i++;
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
		printf("%d\n", get_len_content(line));
		cmd->content[content_index] = malloc(sizeof(char) * get_len_content(line));
		if (cmd->content == NULL)
			exit (1); //A GERER
		content_index += 1;
	}
	return (line_index);
}

int	get_content(char *line, t_cmd *cmd)
{
	int	line_index;
	int	nbr_content;

	line_index = skip_space(line);
	nbr_content = count_content(line);
	if (nbr_content == 0)
		return (0);
	cmd->content = malloc(sizeof(char *) * nbr_content);
	if (cmd->content == NULL)
		exit (1); //A GERER PLUS TARD
	line_index += copy_all_content(line, cmd, nbr_content);
	return (0);
}