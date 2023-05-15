/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:50:43 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 13:59:34 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_unset_error(char *cmd, int s)
{
	g_status = 1;
	if (s == 0)
	{
		ft_printf(2, "export; `%s': not a valid identifier\n", cmd);
		return ;
	}
	if (s == 1)
	{
		ft_printf(2, "%s: event not found\n");
		return ;
	}
}

int	check_unset_error(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '-')
		return (print_unset_error(cmd, 0), 1);
	if (ft_isdigit(cmd[0]) || cmd[0] == '=' || cmd[0] == '\0')
		return (print_unset_error(cmd, 0), 1);
	while (cmd[i] != '\0')
	{	
		if (cmd[i] == '!')
			return (print_unset_error(&cmd[i], 1), 1);
		if (cmd[i] == '@' || cmd[i] == '%' || cmd[i] == '?' \
		|| cmd[i] == '*' || cmd[i] == '\\' || cmd[i] == '~' \
		|| cmd[i] == '-' || cmd[i] == '.' || cmd[i] == '{' \
		|| cmd[i] == '}' || cmd[i] == '#' || cmd[i] == '+' \
		|| cmd[i] == '=' || cmd[i] == '^')
			return (print_unset_error(cmd, 0), 1);
		i++;
	}
	return (0);
}
