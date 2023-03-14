/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:57:45 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 12:41:12 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	print_env_var(char *str, t_env_var *env_list, t_env_main *main_env)
{
	if (str[0] == '$' && str[1] == '?')
	{
		ft_printf("%d", main_env->last_cmd_status);
		return ;
	}
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

void	ft_echo(char **cmd, t_env_var *env_list, t_env_main *main_env)
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
			print_env_var(cmd[i], env_list, main_env);
		else
			ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n)
		ft_printf("\n");
	main_env->last_cmd_status = 0;
}
