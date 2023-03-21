/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:29:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/21 10:35:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	g_status = 0;

void	signal_action(int sig)
{
	if (sig == SIGQUIT)
	{
		g_status = 131;
		return ;
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

void	signal_handler(t_env_main *main_env)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_action;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	main_env->last_cmd_status = g_status;
}

void	termios_init(t_env_main *main_env)
{
	struct termios		termios_new;
	int					rc;

	rc = tcgetattr(0, main_env->tty);
	if (rc)
	{
		perror("tcgetattr");
		exit(1);
	}
	termios_new = *main_env->tty;
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new);
	if (rc)
	{
		perror("tcsetattr");
		exit(1);
	}
}
