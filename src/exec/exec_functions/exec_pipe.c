/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:33:14 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/07 22:47:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("CMD = %s\n", tab[i]);
		i++;
	}
}

static void	check_inout(t_env_pipe *st, t_line *all_cmd)
{
	if (all_cmd->infile != NULL)
		st->input = 1;
	else
		st->input = 0;
	if (all_cmd->outfile != NULL)
		st->output = 1;
	else
		st->output = 0;
}

int	exec_pipe(int argc, char **argv, \
	t_env_main *main_env, t_line *all_cmd)
{
	t_env_pipe	*st;

	st = malloc(sizeof(t_env_pipe));
	if (st == NULL)
		return (ft_printf("Error : %s\n", strerror(errno)));
	check_inout(st, all_cmd);
	if (!open_files(st, all_cmd))
		return (0);
	if (!set_up_struct(st, all_cmd, argc))
		return (0);
	if (!execution(argv, main_env->env, st))
		return (0);
	return (1);
}
