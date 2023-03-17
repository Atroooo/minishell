/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 12:35:47 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_pwd(char **cmd, t_env_main *main_env)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "pwd") != 0)
		return ;
	if (cmd[1])
	{
		main_env->last_cmd_status = 1;
		ft_printf("pwd: too many arguments\n");
		return ;
	}
	main_env->last_cmd_status = 0;
	ft_printf("%s\n", getcwd(NULL, 0));
}