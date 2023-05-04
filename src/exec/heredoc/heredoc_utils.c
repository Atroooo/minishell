/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:50:53 by marvin            #+#    #+#             */
/*   Updated: 2023/05/03 17:50:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*get_delimiter(char *str)
{
	char	*delimiter;

	delimiter = ft_strtrim(str, "< ");
	if (!delimiter)
		return (NULL);
	return (delimiter);
}

static char	*heredoc_parsing(t_line *all_cmd)
{
	char	*delimiter;
	char	*get_str;

	get_str = readline("heredoc> ");
	delimiter = get_delimiter(lst_last(all_cmd->infile)->data);
	if (!delimiter)
		return (NULL);
	if (get_str == NULL)
	{
		ft_printf("End of file : the delimiter was %s\n", delimiter);
		free(delimiter);
		return (NULL);
	}
	else if (ft_strcmp(delimiter, get_str) == 0)
	{
		free(delimiter);
		free(get_str);
		return (NULL);
	}
	free(delimiter);
	if (get_str[0] == '\0')
		return (ft_strdup("\n"));
	return (ft_strjoin(get_str, "\n"));
}

int	heredoc_loop(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env)
{
	char	*tmp_str;
	char	*global_var;
	int		temp_pipe[2];

	pipe(temp_pipe);
	st->infile = temp_pipe[0];
	while (1)
	{
		tmp_str = heredoc_parsing(all_cmd);
		if (!tmp_str)
			break ;
		else
		{
			global_var = replace_global_variable(tmp_str, main_env);
			write(temp_pipe[1], global_var, ft_strlen(global_var));
			free(global_var);
		}
	}
	close(temp_pipe[1]);
	return (1);
}
