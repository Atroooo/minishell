/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:04:32 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/09 19:25:57 by marvin           ###   ########.fr       */
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
	if (error == -1)
	{
		reset_terminal(main_env);
		free_main_env(main_env);
	}
	else if (error == 0)
		exec_hub(&all_cmd, main_env);
}

static void	exec_shell(t_env_main *main_env)
{
	char	*line;

	line = NULL;
	signal_handler();
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
			g_status = 131;
			reset_terminal(main_env);
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
