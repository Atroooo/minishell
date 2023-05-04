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

unsigned char	g_status = 0;

static void	check_param(int argc)
{
	if (argc != 1)
	{
		ft_printf("Usage: ./minishell\n");
		exit(0);
	}
}

static void	exec_core(char *line, t_env_main *main_env)
{
	t_line	all_cmd;
	int		error;

	error = 0;
	error = parsing(line, &all_cmd, main_env);
	main_env->exit_status = g_status;
	if (error == -1)
		free_main_env(main_env);
	else if (error == 0)
		exec_hub(&all_cmd, main_env);
}

static void	exec_shell(t_env_main *main_env)
{
	char	*line;

	line = NULL;
	signal_handler(main_env);
	line = readline("prompt> ");
	while (1)
	{
		while (line != NULL)
		{
			exec_core(line, main_env);
			line = readline("prompt> ");
		}
		if (!line)
		{
			main_env->exit_status = 131;
			free_main_env(main_env);
		}
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
