/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 10:47:29 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"\

void	ft_pwd(char **cmd)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "pwd") != 0)
		return ;
	if (cmd[1])
	{
		ft_printf("pwd: too many arguments\n");
		return ;
	}
	ft_printf("%s\n", getcwd(NULL, 0));
}
