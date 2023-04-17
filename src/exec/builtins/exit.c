/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:32 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/17 15:11:18 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	ft_exit(char **cmd, t_env_main *main_env, t_line *all_cmd)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "exit") != 0)
		return ;
	free_cmd(all_cmd);
	free_inout_list(all_cmd->infile);
	free_inout_list(all_cmd->outfile);
	free_all_exit(main_env);
}
