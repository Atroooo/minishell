/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 15:05:29 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_pwd(char **cmd, t_env_pipe *st)
{
	char	cwd[4096];

	if (!cmd)
		return ;
	if (cmd[1])
	{
		if (ft_strlen(cmd[1]) > 2)
		{
			g_status = 2;
			ft_printf(2, "pwd: --: invalid option\n");
			return ;
		}
		if (ft_strlen(cmd[1]) > 1 && cmd[1][0] == '-' && cmd[1][1] != '-')
		{
			g_status = 2;
			ft_printf(2, "pwd: %s: invalid option\n", cmd[1]);
			return ;
		}
	}
	g_status = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf(st->outfile, "%s\n", cwd);
	cwd[0] = '\0';
}
