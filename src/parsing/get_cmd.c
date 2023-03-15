/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:15:32 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/15 09:48:34 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"


int	get_size(char *line, int *size)
{
	int		i;
	int		nbr_quote;

	i = 0;
	nbr_quote = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		if (line[i] == '\'' || line[i] == '\"')
			i += count_len(&line[i], line[i], &nbr_quote);
		else
			i += 1;
	}
	*size = i;
	return (i - nbr_quote);
}

void	copy_cmd(int size, char *src, char *dest)
{
	int		i;
	char	del;
	int		y;

	i = 0;
	y = 0;
	del = 0;
	while (i < size)
	{
		if ((src[i] == '\'' || src[i] == '\"') && del == 0)
		{
			del = src[i];
			i += 1;
		}
		else if (del != 0 && src[i] == del)
		{
			del = 0;
			i += 1;
		}
		else
		{
			dest[y] = src[i];
			y += 1;
			i += 1;
		}
	}
	dest[y] = '\0';
	printf("%s\n", dest);
}

int	get_cmd(char *line, int *no_command, t_cmd *cmd)
{
	char	*cmd_str;
	int		size;
	int		size_malloc;

	*no_command = FALSE;
	size = 0;
	size_malloc = get_size(line, &size);
	printf("%d\n", size);
	cmd_str = malloc(sizeof(char) * (size_malloc + 1));
	if (cmd_str == NULL)
		exit (1); //A GERER
	copy_cmd(size, line, cmd_str);
	return (size);
}
