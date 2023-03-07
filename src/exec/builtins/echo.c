/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:57:45 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/07 14:55:29 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
    int		i;
    int		n;

    i = 1;
    n = 0;
    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        n = 1;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 2);
        if (args[i + 1])
            ft_putchar_fd(' ', 2);
        i++;
    }
    if (!n)
        ft_putchar_fd('\n', 2);
}