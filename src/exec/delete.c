/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:05:32 by atro              #+#    #+#             */
/*   Updated: 2023/04/17 14:05:44 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_all_cmd(char ***all_cmd)
{
	int	i;

	i = 0;
	while (all_cmd[i])
	{
		printf("CMD %d\n", i);
		print_tab(all_cmd[i]);
		i++;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("CMD = |%s|\n", tab[i]);
		i++;
	}
}
