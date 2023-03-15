/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:56:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/15 17:42:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	check_param(int argc)
{
	if (argc != 1)
	{
		ft_printf("Usage: ./minishell\n");
		exit(0);
	}
}

static void	exec_shell(char **env, t_env_main *main_env)
{
	char		*line;

	signal_handler(main_env);
	line = readline("prompt> ");
	while (1)
	{
		signal_handler(main_env);
		while (line != NULL)
		{
			add_history(line);
			parsing(line, env, main_env);
			free(line);
			line = readline("prompt> ");
		}
		if (!line)
			exit(0);
		rl_clear_history();
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_env_main	*main_env;

	(void) argv;
	check_param(argc);
	main_env = malloc(sizeof(t_env_main));
	if (!main_env)
		exit(0);
	init_main_env(main_env);
	exec_shell(env, main_env);
	return (0);
}
