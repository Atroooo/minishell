/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:56:28 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/27 18:05:21 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*setup_file(char *raw_file)
{
	char	*file;

	file = ft_substr(raw_file, 1, ft_strlen(raw_file));
	if (!file)
		return (NULL);
	file = ft_substr(file, skip_space(file), ft_strlen(file));
	if (!file)
		return (NULL);
	return (file);
}

static char	*setup_cmd(char *cmd, t_env_main *main_env)
{
	char	*s_cmd;

	if (ft_strncmp(cmd, "<", 1) == 0 || ft_strncmp(cmd, ">", 1) == 0)
	{
		if (ft_strncmp(cmd, "<", 1) == 0)
			main_env->input = 1;
		else if (ft_strncmp(cmd, ">", 1) == 0)
			main_env->output = 1;
		s_cmd = setup_file(cmd);
		if (!s_cmd)
			return (NULL);
		return (s_cmd);
	}
	else
	{
		s_cmd = ft_strdup(cmd);
		if (!s_cmd)
			return (NULL);
		return (s_cmd);
	}
	return (NULL);
}

char	**cmd_to_send(t_line *all_cmd, t_env_main *main_env)
{
	char	**s_cmd;
	int		i;
	int		j;
	int		k;

	s_cmd = malloc(sizeof(char) * (get_total_cmd(all_cmd) + 1));
	if (!s_cmd)
		return (NULL);
	i = 0;
	k = 0;
	while (all_cmd->all_cmd[i])
	{
		j = 0;
		while (all_cmd->all_cmd[i][j])
		{
			s_cmd[k] = setup_cmd(all_cmd->all_cmd[i][j], main_env);
			if (!s_cmd[k]) // A FREE
				return (NULL);
			j++;
			k++;
		}
		i++;
	}
	s_cmd[k] = NULL;
	return (s_cmd);
}
