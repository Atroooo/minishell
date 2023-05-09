/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:28:37 by atro              #+#    #+#             */
/*   Updated: 2023/05/09 19:25:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	termios_init(t_env_main *main_env)
{
	struct termios		termios_new;
	int					rc;

	rc = tcgetattr(0, main_env->tty);
	if (rc)
	{
		perror("tcgetattr");
		exit(g_status);
	}
	termios_new = *main_env->tty;
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new);
	if (rc)
	{
		perror("tcsetattr");
		exit(g_status);
	}
}

void	reset_terminal(t_env_main *main_env)
{
	struct termios		termios_new;
	int					rc;

	rc = tcgetattr(0, main_env->tty);
	if (rc)
	{
		perror("tcgetattr");
		exit(g_status);
	}
	termios_new = *main_env->tty;
	termios_new.c_lflag |= ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new);
	if (rc)
	{
		perror("tcsetattr");
		exit(g_status);
	}
}
