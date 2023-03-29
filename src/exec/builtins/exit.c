/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:32 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/23 10:23:35 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_exit(char **cmd, t_env_main *main_env)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "exit") != 0)
		return ;
	free_all_exit(main_env);
}
