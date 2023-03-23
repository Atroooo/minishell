/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:56:05 by vgonnot           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/21 22:35:22 by marvin           ###   ########.fr       */
=======
/*   Updated: 2023/03/23 09:10:43 by vgonnot          ###   ########.fr       */
>>>>>>> master
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

	signal_handler(main_env);
	error = 0;
	line = readline("prompt> ");
	while (1)
	{
		while (line != NULL)
		{
			add_history(line);
			error = parsing(line, &all_cmd);
			if (error == -1)
				exit (1); // ERROR MALLOC FAUT GERER AUTRE FREE
			else if (error == 0)
				exec_hub(&all_cmd, env, main_env);
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
	struct termios	termios_save;
	t_env_main		main_env;

	(void) argv;
	check_param(argc);
	main_env.tty = &termios_save;
	init_main_env(&main_env, env);
	exec_shell(env, &main_env);
	return (0);
}
