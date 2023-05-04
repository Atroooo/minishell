/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:28:37 by atro              #+#    #+#             */
/*   Updated: 2023/05/04 21:31:05 by marvin           ###   ########.fr       */
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

void	reset_terminal(t_env_main *main_env)
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
	termios_new.c_lflag |= ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new);
	if (rc)
	{
		perror("tcsetattr");
		exit(1);
	}
}
