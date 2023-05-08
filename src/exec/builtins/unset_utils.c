/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:50:43 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/08 15:50:58 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_unset_error(char *cmd, int s)
{
	if (s == 0)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	if (s == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": event not found", 2);
		return ;
	}
}
