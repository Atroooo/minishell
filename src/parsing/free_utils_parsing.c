/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 07:19:28 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/17 14:51:51 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	free_list(t_lst *lst)
{
	t_lst	*precedent;

	while (lst != NULL)
	{
		precedent = lst;
		lst = lst->next;
		free(precedent);
	}
}

static void	free_single_cmd(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	free_list(cmd->flag);
	free_list(cmd->content);
	free_list(cmd->infile);
	free_list(cmd->outfile);
}

static void	free_3d_array(char ***array)
{
	int	i;
	int	y;

	i = 0;
	while (array[i] != NULL)
	{
		y = 0;
		while (array[i][y] != NULL)
		{
			free(array[i][y]);
			y++;
		}
		free(array[i]);
		i++;
	}
}

void	free_cmd_struct(t_line *all_cmd)
{
	int	i;

	i = 0;
	while (i < all_cmd->nbr_cmd)
	{
		 free_single_cmd(&all_cmd->cmd[i]);
		i++;
	}
	if (all_cmd->cmd)
		free(all_cmd->cmd);
}

void	quit_function_parsing(t_line *all_cmd)
{
	free_cmd_struct(all_cmd);
	if (all_cmd->all_cmd != NULL)
		free_3d_array(all_cmd->all_cmd);
	perror(strerror(errno));
	exit (1);
}
