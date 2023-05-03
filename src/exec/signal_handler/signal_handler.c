/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:29:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/03 14:19:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

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
		if (g_status != 255)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
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
	main_env->exit_status = g_status;
}
