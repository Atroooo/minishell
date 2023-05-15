/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:29:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 16:20:07 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	signal_action(int sig)
{
	if (sig == SIGQUIT)
	{
		if (g_status == 255)
		{
			g_status = 131;
			exit(g_status);
		}
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		if (g_status != 255)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (g_status == 254)
		{
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
			rl_replace_line("", 0);
			rl_on_new_line();
		}
		g_status = 130;
	}
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_action;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	activate_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	desactivate_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
