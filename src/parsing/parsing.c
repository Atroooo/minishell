/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 16:38:13 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	parsing(char *line, t_environ **env_list)
{
	char		**cmd_line;

	if (!line)
		return ;
	cmd_line = ft_split(line, ' ');
    if (!cmd_line)
    	return ;
    redirect_input(cmd_line);
    redirect_output(cmd_line);
    redirect_output_append(cmd_line);
    ft_echo(cmd_line);
    ft_cd(cmd_line);
    ft_pwd(cmd_line);
    if (ft_strcmp(cmd_line[0], "export") == 0)
    	*env_list = ft_export(cmd_line, *env_list);
    ft_env(cmd_line, *env_list);
    ft_unset(cmd_line, *env_list);
    ft_exit(cmd_line);
}
