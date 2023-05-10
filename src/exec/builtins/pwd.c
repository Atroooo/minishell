/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/10 15:08:55 by vgonnot          ###   ########.fr       */
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
			ft_putendl_fd("pwd: -p: invalid option", 2);
			return ;
		}
	}
	g_status = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, st->outfile);
	cwd[0] = '\0';
}
