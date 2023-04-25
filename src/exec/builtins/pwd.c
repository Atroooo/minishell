/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/24 18:19:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_pwd(char **cmd, t_env_main *main_env)
{
	char	*path;
	
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "pwd") != 0)
		return ;
	if (cmd[1])
	{
		main_env->exit_status = 1;
		printf("pwd: too many arguments\n");
		return ;
	}
	main_env->exit_status = 0;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
