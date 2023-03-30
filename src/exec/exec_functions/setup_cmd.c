/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:56:28 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/30 13:35:02 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*A Protéger*/
static char	*setup_cmd(char *cmd)
{
	char	*s_cmd;

	if (!cmd)
		return (NULL);
	s_cmd = ft_strdup(cmd);
	if (!s_cmd)
		return (NULL);
	return (s_cmd);
}

char	**cmd_to_send(t_line *all_cmd)
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
			s_cmd[k] = setup_cmd(all_cmd->all_cmd[i][j]);
			if (!s_cmd[k])
				return (NULL);
			k++;
		}
	}
	s_cmd[k] = NULL;
	return (s_cmd);
}
