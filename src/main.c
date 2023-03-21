/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:56:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/21 09:55:15 by vgonnot          ###   ########.fr       */
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
	char	*line;
	t_line	all_cmd;
	int		error;

	//signal_handler(main_env);
	error = 0;
	line = readline("prompt> ");
	while (1)
	{
		while (line != NULL)
		{
			add_history(line);
			error = parsing(line, &all_cmd, env, main_env);
			if (error == -1)
				exit (1) // ERROR MALLOC FAUT GERER AUTRE FREE
			//else if (error == 0)
				//MET TON EXEC ICI
			free(line);
			line = readline("prompt> ");
		}
		if (!line)
			exit(0);
		//rl_clear_history();
	}
}

int	main(int argc, char *argv[], char *env[])
{
	struct termios	termios_save;
	t_env_main		main_env;

	(void) argv;
	check_param(argc);
	main_env.tty = &termios_save;
	init_main_env(&main_env, env);
	exec_shell(env, &main_env);
	return (0);
}
