/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:56:28 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/06 22:44:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

/*A Protéger*/
void	concat_cmd(char **cmd, char *s_cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			s_cmd[k] = cmd[i][j];
			j++;
			k++;
		}
		if (cmd[i + 1])
		{
			s_cmd[k] = ' ';
			k++;
		}
		j = 0;
		i++;
	}
	s_cmd[k] = '\0';
}

static char	*setup_cmd(char **cmd)
{
	char	*s_cmd;
	int		total_index;
	int		i;

	if (!cmd)
		return (NULL);
	i = 0;
	total_index = 0;
	while (cmd[i])
	{
		total_index += ft_strlen(cmd[i]);
		i++;
	}
	s_cmd = malloc(sizeof(char) * (total_index + i + 1));
	if (!s_cmd)
		return (NULL);
	concat_cmd(cmd, s_cmd);
	// i = 0;
	// while (cmd[i])
	// {
	// 	ft_strcpy(s_cmd + ft_strlen(s_cmd), cmd[i]);
	// 	if (cmd[i + 1])
	// 		ft_strcpy(s_cmd + ft_strlen(s_cmd), " ");
	// 	i++;
	// }
	return (s_cmd);
}

char	**cmd_to_send(t_line *all_cmd)
{	
	char	**s_cmd;
	int		i;
	int		k;

	if (!all_cmd->all_cmd)
		return (NULL);
	s_cmd = malloc(sizeof(char *) * (all_cmd->nbr_cmd + 1));
	if (!s_cmd)
		return (NULL);
	i = -1;
	k = 0;
	while (all_cmd->all_cmd[++i])
	{
		s_cmd[k] = setup_cmd(all_cmd->all_cmd[i]);
		if (!s_cmd[k])
			return (NULL);
		k++;
	}
	s_cmd[k] = NULL;
	return (s_cmd);
}
