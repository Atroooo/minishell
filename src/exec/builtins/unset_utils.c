/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:50:43 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 08:26:15 by vgonnot          ###   ########.fr       */
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
