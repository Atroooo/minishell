/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:29:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 22:16:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

//Reste le cas ctrl + \ qui doit rien ecrire
void	signal_action(int sig, siginfo_t *info, void *context)
{
	struct termios	term;

	(void) info;
	(void) context;
	if (sig == SIGQUIT)
	{
		if (tcsetattr(2, NOFLSH, &term) == -1)
			ft_putstr_fd("Error: tcsetattr\n", 2);
		else
			ft_putchar_fd(0, 2);
		return ;
	}
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
