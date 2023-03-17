/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:58:47 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 12:38:15 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_cd(char **cmd, t_env_main *main_env)
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
	{
		main_env->last_cmd_status = 1;
		return ;
	}
	if (chdir(path) == -1)
	{
		ft_printf("bash: cd: %s no such file or directory\n", path);
		main_env->last_cmd_status = 1;
		free(path);
		return ;
	}
	main_env->last_cmd_status = 0;
}
