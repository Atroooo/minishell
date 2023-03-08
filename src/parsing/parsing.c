/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:42:21 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 11:21:51 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	parsing(char *line)
{
	char	**cmd_line;

	cmd_line = ft_split(line, ' ');
    if (!cmd_line)
        return ;
    redirect_input(cmd_line);
    redirect_output(cmd_line);
    redirect_output_append(cmd_line);
    ft_echo(cmd_line);
    ft_cd(cmd_line);
    ft_pwd(cmd_line);
}
