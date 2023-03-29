/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:33:14 by atro              #+#    #+#             */
/*   Updated: 2023/03/29 09:31:35 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	exec_pipe(int argc, char **argv, t_env_main *main_env)
{
	t_env_pipe	*st;

	st = malloc(sizeof(t_env_pipe));
	if (st == NULL)
		return (ft_printf("Error : %s\n", strerror(errno)));
	st->input = main_env->input;
	st->output = main_env->output;
	if (!open_files(argv, st))
		return (0);
	if (!set_up_struct(st, argc))
		return (0);
	execution(argv, main_env->env, st);
	return (1);
}
