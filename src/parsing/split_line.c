/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:07:14 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/13 13:07:41 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	count_split(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		i++;
	}
	return (i);
}

static void	set_up_newlst(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->flag = NULL;
	cmd->content = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
}

int	get_element(int *i, \
			int (*get)(char *, t_cmd *), char *line, t_cmd *cmd)
{
	int	temp;

	temp = get(line, cmd);
	if (temp == -1)
		return (-1);
	*i += temp;
	return (0);
}

static int	initialize_variable( \
			t_cmd *cmd, int *error, int *no_command, int *is_echo)
{
	*no_command = TRUE;
	*is_echo = FALSE;
	*error = 0;
	set_up_newlst(cmd);
	return (0);
}

int	set_up_arg(char *line, t_cmd *cmd)
{
	int	i;
	int	error;
	int	no_command;
	int	is_echo;

	i = initialize_variable(cmd, &error, &no_command, &is_echo);
	while (line[i] != '\0' && error == 0)
	{
		i += skip_space(&line[i]);
		if (line[i] == '<' || line[i] == '>')
			error = get_element(&i, &get_file, &line[i], cmd);
		else if (no_command == TRUE && error == 0)
		{
			error = get_element(&i, &get_cmd, &line[i], cmd);
			no_command = FALSE;
		}
		else if (line[i] == '-' && error == 0 && is_echo == FALSE)
			error = get_element(&i, &get_flag, &line[i], cmd);
		else if (error == 0)
		{
			error = get_element(&i, &get_content, &line[i], cmd);
			if (ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->content->data)) == 0)
				is_echo = TRUE;
		}
	}
	return (error);
}

int	initialize_value(t_line *all_cmd, char **splitted_line)
{
	all_cmd->all_cmd = NULL;
	all_cmd->nbr_cmd = 0;
	all_cmd->cmd = NULL;
	all_cmd->nbr_cmd = count_split(splitted_line);
	all_cmd->cmd = malloc(sizeof(t_cmd) * (all_cmd->nbr_cmd));
	if (all_cmd->cmd == NULL)
		return (-1);
	return (0);
}

int	split_line(char *line, t_line *all_cmd)
{
	char	**splitted_line;
	int		i;
	int		error;

	error = 0;
	i = 0;
	splitted_line = split_skip_quote(line);
	if (splitted_line == NULL)
		return (-1);
	error = initialize_value(all_cmd, splitted_line);
	while (splitted_line[i] != NULL && error == 0)
	{
		error = set_up_arg(splitted_line[i], &all_cmd->cmd[i]);
		i++;
	}
	ft_free_2d_array(splitted_line);
	return (error);
}
