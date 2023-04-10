/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 07:31:45 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/10 17:04:01 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*error_case(char *s)
{
	printf("syntax error near unexpected token `%s'\n", s);
	return (NULL);
}

int	check_if_pipe(char *line, int *consecutive_pipe)
{
	int	i;

	i = 0;
	while (line[i] == '|')
	{
		consecutive_pipe += 1;
		i++;
	}
	return (i);
}

int	check_char(char c, int *pipe, int *consecutive_pipe, int *only_space)
{
	if (c == '|')
	{
		*pipe = 1;
		*consecutive_pipe += 1;
	}
	else
	{
		*only_space = 0;
		*consecutive_pipe = 0;
	}
	return (1);
}

char	*last_char_pipe(char *line)
{
	char	*str;
	char	*new_line;

	ft_printf("> ");
	str = get_next_line(0);
	if (str == NULL)
		return (NULL);
	new_line = ft_strjoin(line, str);
	free(line);
	free(str);
	return (new_line);
}

char	*check_if_pipe_error(char *line) //A CHANGER NE MARCHE PLUS 
{
	int	pipe;
	int	consecutive_pipe;
	int	only_space;
	int	i;

	pipe = 0;
	consecutive_pipe = 0;
	only_space = 1;
	i = 0;
	if (line[ft_strlen(line) - 1] == '|' && line[ft_strlen(line) - 2] != '|')
		line = last_char_pipe(&line[0]);
	while (line[i] != '\0')
	{
		i += skip_space(&line[i]);
		i += check_char(line[i], &pipe, &consecutive_pipe, &only_space);
		i += check_if_pipe(&line[i], &consecutive_pipe);
		if ((consecutive_pipe == 2 && only_space == 1) || consecutive_pipe > 3)
			return (error_case("||"));
		else if (pipe == 1 && only_space == 1)
			return (error_case("|"));
	}
	return (line);
}
