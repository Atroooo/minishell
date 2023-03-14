/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:57:45 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 10:46:09 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	print_env_var(char *str, t_environ *env_list)
{
	if (!env_list)
		ft_printf("\n");
	while (env_list)
	{
		if (env_list->name && ft_strcmp(str + 1, env_list->name) == 0)
		{
			ft_printf("%s", env_list->value);
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
			ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n)
		ft_printf("\n");
}
