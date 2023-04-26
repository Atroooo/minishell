/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 07:31:45 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/26 18:28:54 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	error_case(char *s, int *error)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("`", 2);
	*error = 1;
	return (1);
}

int	check_if_pipe(char *line, int *consecutive_pipe)
{
	int	i;

	i = 0;
	while (line && line[i] == '|')
	{
		*consecutive_pipe += 1;
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
	else if (c == '\0')
		return (0);
	else
	{
		*only_space = 0;
		*consecutive_pipe = 0;
	}
	return (1);
}

static int	check_if_error(char *line, int *error)
{
	int	pipe;
	int	consecutive_pipe;
	int	only_space;
	int	i;

	pipe = 0;
	consecutive_pipe = 0;
	only_space = 1;
	i = 0;
	while (line && line[i] != '\0')
	{
		i += skip_space(&line[i]);
		if (line[i] == '\'' || line[i] == '\"')
			i += skip_in_between(&line[i], line[i]);
		else
		{
			i += check_char(line[i], &pipe, &consecutive_pipe, &only_space);
			i += check_if_pipe(&line[i], &consecutive_pipe);
			if ((consecutive_pipe == 2 && only_space == 1) \
				|| consecutive_pipe > 3)
				return (error_case("||", error));
			else if ((pipe == 1 && only_space == 1) || consecutive_pipe == 3 \
					|| (consecutive_pipe == 2 && line[i - 2] == ' '))
				return (error_case("|", error));
		}
	}
	return (0);
}

static int	check_if_last_char_pipe(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len >= 0 && (str[len] == ' '))
		len--;
	if (str[len] == '|')
		return (1);
	return (0);
}

static char	*last_char_pipe(char *line, int *error)
{
	char	*str;
	char	*new_line;
	int		last_char_pipe;

	str = readline("> "); //dans le cas ou on ctrl + D : str = NULL : donc a fix
	if (str == NULL)
		return (free(line), NULL);
	last_char_pipe = check_if_last_char_pipe(str);
	while (last_char_pipe && check_if_error(str, error) == 0)
	{
		free(str);
		str = readline("> ");
		if (str == NULL)
			return (NULL);
	}
	new_line = ft_strjoin(line, str);
	free(line);
	free(str);
	return (new_line);
}

char	*check_if_pipe_error(char *line, t_env_main *main_env, int *error)
{
	char	*new_line;
	int		len;

	if (check_if_error(line, error))
		return (line);
	len = ft_strlen(line);
	if (len > 0 && check_if_last_char_pipe(line))
	{
		line = last_char_pipe(line, error);
		if (line == NULL)
			return (NULL);
		if (error)
			return (line);
		new_line = replace_global_variable(line, main_env);
		free(line);
		if (new_line == NULL)
			return (NULL);
		if (check_if_error(line, error))
			return (line);
		return (new_line);
	}
	return (line);
}
