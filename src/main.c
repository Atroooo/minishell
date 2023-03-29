/************************************************************************ */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:56:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/29 17:09:34 by vgonnot          ###   ########.fr       */
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

static void	exec_shell(t_env_main *main_env)
{
	char	*line;
	t_line	all_cmd;
	int		error;

	error = 0;
	signal_handler(main_env);
	line = readline("prompt> ");
	while (1)
	{
		while (line != NULL)
		{
			add_history(line);
			error = parsing(line, &all_cmd, main_env);
			error = 1;
			if (error == -1)
				free_all_exit(main_env);
			else if (error == 0)
				exec_hub(&all_cmd, main_env);
			free(line);
			line = readline("prompt> ");
		}
		if (!line)
			exit(0); //FAUT FREE
		rl_clear_history();
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
	exec_shell(&main_env);
	return (0);
}
