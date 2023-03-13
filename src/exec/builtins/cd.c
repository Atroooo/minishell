/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:58:47 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/13 15:03:33 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_cd(char **cmd)
{
	char	*path;

	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "cd") != 0)
		return ;
	if (cmd[1] == NULL)
		path = ft_strdup(getenv("HOME"));
	else
		path = ft_strdup(cmd[1]);
	if (path == NULL)
		return ;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" no such file or directory\n", 2);
		free(path);
		return ;
	}
}