/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:57:45 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/26 16:10:15 by lcompieg         ###   ########.fr       */
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

void	ft_echo(char **cmd, t_env_main *main_env)
{
	int	i;
	int	n;

	if (!cmd)
		return ;
	i = 1;
	n = 0;
	while (cmd[i] && check_if_flag(cmd[i]))
	{
		n = 1;
		i++;
	}
	while (cmd[i])
	{
		if (ft_strcmp("$?", cmd[i]) == 0)
			printf("%d", main_env->exit_status);
		else
			printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!n)
		printf("\n");
	main_env->exit_status = 0;
}
