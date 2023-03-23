/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:28:02 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/22 20:55:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	redirect_input(char **cmd)
{
	int	tube[2];
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<") == 0)
		{
			if (cmd[i + 1] == NULL)
				return ;
			pipe(tube);
			close(0);
			dup2(tube[0], 0);
		}
		i++;
	}
}

void	redirect_output(char **cmd)
{
	int	tube[2];
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">") == 0)
		{
			if (cmd[i + 1] == NULL)
				return ;
			pipe(tube);
			close(1);
			dup2(tube[1], 1);
		}
		i++;
	}
}

void	redirect_output_append(char **cmd)
{
	int	tube[2];
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">>") == 0)
		{
			if (cmd[i + 1] == NULL)
				return ;
			pipe(tube);
			dup2(tube[0], 0);
			dup2(tube[1], 1);
		}
		i++;
	}
}
