/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:56:28 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/28 11:10:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*A Protéger*/
char	*setup_file(char *raw_file)
{
	char	*file;

	if (!raw_file)
		return (NULL);
	file = ft_strtrim(raw_file, "<> ");
	if (!file)
		return (NULL);
	return (file);
}

static char	*setup_cmd(char *cmd, t_env_main *main_env)
{
	char	*s_cmd;

	if (!cmd)
		return (NULL);
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
}

char	**cmd_to_send(t_line *all_cmd, t_env_main *main_env)
{
	char	**s_cmd;
	int		i;
	int		j;
	int		k;

	if (!all_cmd->all_cmd)
		return (NULL);
	s_cmd = malloc(sizeof(char *) * (get_total_cmd(all_cmd) + 1));
	if (!s_cmd)
		return (NULL);
	i = -1;
	k = 0;
	while (all_cmd->all_cmd[++i])
	{
		j = -1;
		while (all_cmd->all_cmd[i][++j])
		{
			s_cmd[k] = setup_cmd(all_cmd->all_cmd[i][j], main_env);
			if (!s_cmd[k])
				return (NULL);
			k++;
		}
	}
	s_cmd[k] = NULL;
	return (s_cmd);
}
