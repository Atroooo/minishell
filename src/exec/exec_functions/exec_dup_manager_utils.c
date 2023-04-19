/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dup_manager_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:51:51 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/19 14:51:54 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	check_spe_outfile(t_env_pipe *st, t_line *all_cmd)
{
	t_lst	*tmp;

	tmp = all_cmd->outfile;
	while (tmp)
	{
		if (tmp->index == st->i)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	open_outfile(t_env_pipe *st, t_line *all_cmd)
{
	t_lst	*tmp;

	tmp = all_cmd->outfile;
	while (tmp)
	{
		if (tmp->index == st->i)
		{
			if (!setup_outfile(st, tmp->data))
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
