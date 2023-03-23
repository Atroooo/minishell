/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:33:14 by atro              #+#    #+#             */
/*   Updated: 2023/03/21 10:03:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	exec_pipe(int argc, char **argv, char *env[], t_env_main *main_env)
{
	t_env_pipe	*st;

	if (argc < 5)
		return (ft_printf("Error : not enough arguments\n"));
	st = malloc(sizeof(t_env_pipe));
	if (st == NULL)
	{
		main_env->last_cmd_status = 1;
		return (ft_printf("Error : %s\n", strerror(errno)));
	}
	if (!open_files(argc, argv, st))
	{
		main_env->last_cmd_status = 1;
		return (1);
	}
	if (!set_up_struct(st, argc, argv))
	{
		main_env->last_cmd_status = 1;
		return (1);
	}
	execution(argv, env, st);
	main_env->last_cmd_status = 0;
	return (0);
}
