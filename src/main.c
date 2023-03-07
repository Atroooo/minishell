/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:56:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/07 14:54:51 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;

	(void) argv;
	(void) argc;
	(void) env;
	line = readline("prompt> ");
	while (line != NULL)
	{
		add_history(line);
		parsing(line);
		free(line);
		line = readline("prompt> ");
	}
	rl_clear_history();
	return (0);
}
