/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/10 15:48:23 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	parsing(char *line, char *env[], t_environ **env_list )
{
	char		**cmd_line;
    char		**strr; 

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
    if (ft_strcmp(cmd_line[0], "exec") == 0)
    {
        strr = malloc(sizeof(char *) * 5);
		strr[0] = " ";
		strr[1] = " ";
		strr[2] = "ls -la";
		strr[3] = "wc -l";
		strr[4] = "outfile";
        exec_cmd(5, strr, env);
    }

}
