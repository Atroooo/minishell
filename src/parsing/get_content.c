/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:35:38 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/12 20:39:03 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// 	int		i;
// 	int		content_nbr;
// 	char	quote;

// 	i = 0;
// 	content_nbr = 1;
// 	quote = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == ' ' && quote == 0)
// 		{
// 			content_nbr += 1;
// 			printf("i = %d %s ", i, &line[i]);
// 			i += skip_space(&line[i]);
// 			if ((line[i] == '\'' || line[i] == '\"') && quote == 0)
// 			{
// 				quote = line[i];
// 				i++;
// 			}
// 		}
// 		if (quote != 0 && quote == line[i])
// 			quote = 0;
// 		if (line[i] != '\0')
// 			i++;
// 	}
// 	return (content_nbr);
// }

int	get_len_content(char *line)
{
	int		i;
	int		y;
	char	selector;

	if (line == NULL)
		return (0);
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
	printf(" %d ", i);
	return (i);
}

static int	count_content(char *line) //CASSER
{
	int		content_nbr;
	int		i;
	int		temp;

	content_nbr = 0;
	temp = get_len_content(line);
	i = temp;
	while (temp > 0)
	{
		temp = get_len_content(&line[i]);
		i += temp;
		content_nbr += 1;
	}
	return (content_nbr);
}

int	copy_all_content(char *line, t_cmd *cmd, int nbr_content)
{
	int	line_index;
	int	content_index;

	line_index = 0;
	content_index = 0;
	while (content_index < nbr_content)
	{
		cmd->content[content_index] = malloc(sizeof(char) * get_len_content(&line[line_index]) + 1);
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

	if (line == NULL)
		return (0);
	if (line[0] == 0)
		return (0);
	//printf("%d\n", count_content(&line[line_index]));
	nbr_content = count_content(&line[line_index]);
	if (nbr_content == 0)
		return (0);
	cmd->content = malloc(sizeof(char *) * nbr_content);
	if (cmd->content == NULL)
		exit (1); //A GERER PLUS TARD
	line_index += copy_all_content(line, cmd, nbr_content);
	return (0);
}
