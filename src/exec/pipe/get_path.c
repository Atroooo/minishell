/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:55:29 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 13:36:36 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	join_path(char **path_split, char *cmd, int index, t_env *st)
{
	char	*temp;

	if (index == 0)
		temp = ft_strjoin(&path_split[0][5], "/");
	else
		temp = ft_strjoin(path_split[index], "/");
	if (temp == NULL)
		quit_function(st, 0);
	free(path_split[index]);
	path_split[index] = ft_strjoin(temp, cmd);
	if (path_split[index] == NULL)
		quit_function(st, 0);
	free(temp);
}

void	set_path(char **path_split, char *cmd, t_env *st)
{
	int		index;

	index = 0;
	while (path_split[index])
	{
		join_path(path_split, cmd, index, st);
		index++;
	}
}

char	*check_if_cmd_exist(char **path_split, char *temp)
{
	int		ac;
	int		i;

	ac = -1;
	i = 0;
	while (ac == -1 && path_split[i])
		ac = access(path_split[i++], X_OK);
	if (ac != -1)
	{
		temp = ft_strjoin(temp, path_split[i -1]);
		ft_free_2d_array(path_split);
		return (temp);
	}
	ft_free_2d_array(path_split);
	return (NULL);
}

char	*get_path(char *cmd, char *paths, t_env *st)
{
	char	**path_split;
	char	*temp;

	temp = NULL;
	if (access(cmd, X_OK) != -1)
		return (ft_strjoin(temp, cmd));
	path_split = ft_split(paths, ':');
	if (path_split == NULL)
		return (NULL);
	set_path(path_split, cmd, st);
	return (check_if_cmd_exist(path_split, temp));
}
