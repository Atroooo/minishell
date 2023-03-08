/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:17:56 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/08 11:25:23 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void    ft_pwd(char **cmd)
{
    if (!cmd)
        return ;
    if (ft_strcmp(cmd[0], "pwd") != 0)
        return ;
    if (cmd[1])
    {
        ft_putstr_fd("pwd: too many arguments\n", 2);
        return ;
    }
    ft_putstr_fd(getcwd(NULL, 0), 2);
    ft_putchar_fd('\n', 2);
}