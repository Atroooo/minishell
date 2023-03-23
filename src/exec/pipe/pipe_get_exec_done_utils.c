/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_done_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:05:58 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/14 11:02:52 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	path_is_null(t_env_pipe *st, char **arg_vec, char **argv)
{
	char	*temp;

	temp = ft_strjoin(argv[st->actual_pipe + 2 + st->hdoc], \
	": command not found\n");
	if (temp != NULL)
	{
		ft_putstr_fd(temp, 2);
		free(temp);
	}
	ft_free_2d_array(arg_vec);
	quit_function(st, -1);
}

void	no_path(t_env_pipe *st, char **arg_vec)
{
	ft_free_2d_array(arg_vec);
	free_pipe(st);
	return ;
}
