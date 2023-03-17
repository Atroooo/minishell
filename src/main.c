/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neoff <neoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:56:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/16 10:31:32 by neoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_line	all_cmd;

	line = readline("prompt> ");
	while (line != NULL)
	{
		add_history(line);
		parsing(line, &all_cmd);
		free(line);
		line = readline("prompt> ");
	}
	//rl_clear_history();
	return (0);
}
