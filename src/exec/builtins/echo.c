/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:57:45 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/09 19:26:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	check_if_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (i > 1 && str[i] == '\0')
		return (1);
	return (0);
}

void	ft_echo(char **cmd, t_env_pipe *st)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i] && check_if_flag(cmd[i]))
	{
		n = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], st->outfile);
		if (cmd[i + 1])
			write(st->outfile, " ", 1);
		i++;
	}
	if (!n)
		write(st->outfile, "\n", 1);
	g_status = 0;
}
