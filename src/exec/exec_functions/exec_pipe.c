/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:33:14 by atro              #+#    #+#             */
/*   Updated: 2023/03/23 16:24:15 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	exec_pipe(int argc, char **argv, t_env_main *main_env)
{
	t_env_pipe	*st;

	st = malloc(sizeof(t_env_pipe));
	if (st == NULL)
	{
		main_env->last_cmd_status = 1;
		return (ft_printf("Error : %s\n", strerror(errno)));
	}
	if (argc > 3 && !open_files(argc, argv, st))
	{
		main_env->last_cmd_status = 1;
		return (1);
	}
	if (!set_up_struct(st, argc))
	{
		main_env->last_cmd_status = 1;
		return (1);
	}
	execution(argv, main_env->env, st);
	main_env->last_cmd_status = 0;
	return (0);
}
