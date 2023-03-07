/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:28:02 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/07 14:50:00 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	redirect_input(char **argv)
{
	int	tube[2];
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "<") == 0)
		{
			if (argv[i + 1] == NULL)
				return ;
			pipe(tube);
			close(0);
			dup2(tube[0], 0);
		}
		i++;
	}
}

void	redirect_output(char **argv)
{
	int	tube[2];
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], ">") == 0)
		{
			if (argv[i + 1] == NULL)
				return ;
			pipe(tube);
			close(1);
			dup2(tube[1], 1);
		}
		i++;
	}
}

void	readn_input(char **argv)
{
	int	tube[2];
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "<<") == 0)
		{
			if (argv[i + 1] == NULL)
				return ;
			pipe(tube);
			dup2(tube[0], 0);
			dup2(tube[1], 1);
		}
	}
}

void	redirect_output_append(char **argv)
{
	int	tube[2];
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], ">>") == 0)
		{
			if (argv[i + 1] == NULL)
				return ;
			pipe(tube);
			dup2(tube[0], 0);
			dup2(tube[1], 1);
		}
		i++;
	}
}
