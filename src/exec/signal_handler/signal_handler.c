/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atro <atro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:29:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/13 14:12:36 by atro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

//Reste le cas ou on ctrl + c ou ctrl + \\ au tout debut sans rien ecrire
void	signal_action(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		signal_handler();
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
