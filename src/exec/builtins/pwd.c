/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 08:24:02 by vgonnot          ###   ########.fr       */
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
		if (cmd[1][0] == '-')
		{
			g_status = 2;
			ft_printf(2, "pwd: -p: invalid option\n");
			return ;
		}
	}
	g_status = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf(st->outfile, "%s\n", cwd);
	cwd[0] = '\0';
}
