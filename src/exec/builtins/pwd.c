/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/01 15:06:02 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_pwd(char **cmd)
{
	char	cwd[4096];

	if (!cmd)
		return ;
	if (cmd[1])
	{
		g_status = 1;
		if (cmd[1][0] == '-')
		{
			ft_putendl_fd("pwd: -p: invalid option", 2);
			return ;
		}
		ft_putendl_fd("pwd: too many argument", 2);
		return ;
	}
	g_status = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	cwd[0] = '\0';
}
