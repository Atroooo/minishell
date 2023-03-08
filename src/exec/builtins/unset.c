/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:42:31 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/08 15:21:34 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	find_in_list(char *name, t_environ *env_list)
{
	t_environ   *temp;

	if (!name || !env_list)
		return ;
	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			temp->name = NULL;
			temp->value = NULL;
			return ;
		}
		temp = temp->next;
	}
}
void    ft_unset(char **cmd, t_environ *env_list)
{
    int     i;

    if (!cmd)
        return ;
    if (ft_strcmp(cmd[0], "unset") != 0)
        return ;
    i = 1;
    while (cmd[i])
    {
        find_in_list(cmd[i], env_list);
        i++;
    }
}