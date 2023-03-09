/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:57:45 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/09 11:20:07 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	n;

	if (!cmd)
		return ;
	i = 1;
	n = 0;
	if (cmd[1] && ft_strcmp(cmd[1], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 2);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 2);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 2);
}
