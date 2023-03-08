/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:56:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/08 16:28:53 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	init_struct(t_environ *env_list)
{
	env_list = malloc(sizeof(t_environ));
	if (!env_list)
		exit(0);
}

void	init_env(t_environ **env_list)
{
	char    **env;
	int		i;

	env = ft_split(getenv("PATH"), ':');
	if (!env)
		exit(0);
	i = 0;
	while (env[i])
	{
		*env_list = add_env_value(env[i], *env_list);
		i++;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_environ	*env_list;
	char		*line;

	(void) argv;
	(void) argc;
	(void) env;
	env_list = NULL;
	init_struct(env_list);
	init_env(&env_list);
	signal_handler();
	line = readline("prompt> ");
	while (1)
	{
		signal_handler();
		while (line != NULL)
		{
			add_history(line);
			parsing(line, &env_list);
			free(line);
			line = readline("prompt> ");
		}
		if (!line)
			exit(0);
		rl_clear_history();
	}
	return (0);
}
