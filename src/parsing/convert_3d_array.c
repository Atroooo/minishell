/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_3d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:35:51 by neoff             #+#    #+#             */
/*   Updated: 2023/03/21 09:51:16 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	count_lst(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i += 1;
		lst = lst->next;
	}
	return (i);
}

int	count_nbr_element(t_cmd cmd)
{
	int	i;

	i = 0;
	if (cmd.cmd != NULL)
		i += 1;
	i += count_lst(cmd.flag);
	i += count_lst(cmd.content);
	i += count_lst(cmd.infile);
	i += count_lst(cmd.outfile);
	return (i);
}

static char	*copy_command(char *src)
{
	char	*dest;

	dest = NULL;
	dest = ft_strcpy(src, dest);
	if (dest == NULL)
		exit (1); // A GERER PLUS TARD
	return (ft_strcpy(src, dest));
}

static void	get_all_command(t_lst *lst, char **arg, int *index)
{
	t_lst	*temp;
	int		i;

	i = 0;
	while (lst != NULL)
	{
		arg[i] = copy_command(lst->data);
		lst = lst->next;
		*index += 1;
		i++;
	}
}

void	copy_all_arg(char **arg, t_cmd *cmd)
{
	int	index;

	index = 0;
	get_all_command(cmd->infile, &arg[index], &index);
	get_all_command(cmd->outfile, &arg[index], &index);
	if (cmd->cmd != NULL)
		arg[index++] = copy_command(cmd->cmd);
	get_all_command(cmd->flag, &arg[index], &index);
	get_all_command(cmd->content, &arg[index], &index);
	arg[index] = NULL;
	ft_print_2d_array(arg);
}

int	convert_in_3d_array(t_line *all_cmd)
{
	int	i;

	i = 0;
	all_cmd->all_cmd = malloc(sizeof(char **) * (all_cmd->nbr_cmd + 1));
	if (all_cmd->all_cmd == NULL)
		return (-1);
	while (i < all_cmd->nbr_cmd)
	{
		all_cmd->all_cmd[i] = malloc(sizeof(char *) * (count_nbr_element(all_cmd->cmd[i]) + 1));
		if (all_cmd->all_cmd[i] == NULL)
			return (-1);
		copy_all_arg(all_cmd->all_cmd[i], &all_cmd->cmd[i]);
		i++;
	}
	all_cmd->all_cmd[i] = NULL;
}
