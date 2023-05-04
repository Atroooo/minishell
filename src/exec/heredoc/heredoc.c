/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:31:40 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/04 15:18:08 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	check_hdoc(t_line *all_cmd)
{
	t_lst	*tmp;

	if (!all_cmd->infile || !lst_last(all_cmd->infile)->data)
		return (0);
	tmp = all_cmd->infile;
	while (tmp)
	{
		if (ft_strnstr(tmp->data, "<<", 2) != NULL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	heredoc(t_env_pipe *st, t_line *all_cmd, t_env_main *main_env)
{
	int		return_value;

	if (check_hdoc(all_cmd) == 0)
		return (0);
	return_value = heredoc_loop(st, all_cmd, main_env);
	if (return_value == -1)
		return (-1);
	return (return_value);
}
