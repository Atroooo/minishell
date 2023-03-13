/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:57:45 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/13 15:01:59 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	print_env_var(char *str, t_environ *env_list)
{
	if (!env_list)
		ft_putchar_fd('\n', 2);
	while (env_list)
	{
		if (env_list->name && ft_strcmp(str + 1, env_list->name) == 0)
		{
			ft_putstr_fd(env_list->value, 2);
			return ;
		}
		env_list = env_list->next;
	}
}

void	ft_echo(char **cmd, t_environ *env_list)
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
		if (cmd[i][0] == '$')
			print_env_var(cmd[i], env_list);
		else
			ft_putstr_fd(cmd[i], 2);
		if (cmd[i + 1])
			ft_putchar_fd(' ', 2);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 2);
}
