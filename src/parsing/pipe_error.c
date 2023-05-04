/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 07:31:45 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/04 15:30:32 by vgonnot          ###   ########.fr       */
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

static int	check_if_error(char *line, int *error)
{
	int	pipe;
	int	consecutive_pipe;
	int	only_space;
	int	i;
	int	quote;

	pipe = var_init(&quote, &consecutive_pipe, &only_space, &i);
	while (line && line[i] != '\0')
	{
		i += skip_space(&line[i]);
		if (check_if_quote_increment(line[i], &quote))
			i += skip_in_between(&line[i], line[i]);
		else
		{
			i += check_char(line[i], &pipe, &consecutive_pipe, &only_space);
			i += check_if_pipe(&line[i], &consecutive_pipe, &quote);
			if (first_error_case(consecutive_pipe, only_space, quote))
				return (error_case("||", error));
			else if ((pipe == 1 && only_space == 1 && quote == 0) \
				|| consecutive_pipe == 3 \
				|| (consecutive_pipe == 2 && line[i - 2] == ' ' && quote == 0))
				return (error_case("|", error));
		}
	}
	return (0);
}

static int	check_if_last_char_pipe(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	while (len > 0 && (str[len] == ' '))
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

	str = readline("> ");
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
