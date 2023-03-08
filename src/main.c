/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:56:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/07 16:47:46 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;

	(void) argv;
	(void) argc;
	(void) env;

	signal_handler();
	line = readline("prompt> ");
	while (1)
	{
		signal_handler();
		while (line != NULL)
		{
			add_history(line);
			parsing(line);
			free(line);
			line = readline("prompt> ");
		}
		if (!line)
			exit(0);
		rl_clear_history();
	}
	return (0);
}
