/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/26 09:51:38 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_pwd(char **cmd, t_env_main *main_env)
{
	char	*pwd;

	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "pwd") != 0)
		return ;
	if (cmd[1])
	{
		main_env->exit_status = 1;
		if (cmd[1][0] == '-')
			printf("pwd: -p: invalid option\n");
		return ;
	}
	main_env->exit_status = 0;
	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
}
