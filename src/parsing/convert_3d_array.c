/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_3d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:35:51 by neoff             #+#    #+#             */
/*   Updated: 2023/03/20 09:27:58 by vgonnot          ###   ########.fr       */
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

static char	*copy_command(char *src, int *index)
{
	char	*dest;

	(void) index;
	dest = NULL;
	dest = ft_strcpy(src, dest);
	if (dest == NULL)
		exit (1); // A GERER PLUS TARD
	return (ft_strcpy(src, dest));
}

void	copy_all_arg(char **arg, t_cmd *cmd)
{
	int	index;

	index = 0;
	while (cmd->infile != NULL)
	{
		arg[index] = copy_command(cmd->infile->data, &index);
		cmd->infile = cmd->infile->next;
		index += 1;
	}
	while (cmd->outfile != NULL)
	{
		arg[index] = copy_command(cmd->outfile->data, &index);
		cmd->outfile = cmd->outfile->next;
		index += 1;
	}
	if (cmd->cmd != NULL)
	{
		arg[index] = copy_command(cmd->cmd, &index);
		index += 1;
	}
	while (cmd->flag != NULL)
	{
		arg[index] = copy_command(cmd->flag->data, &index);
		cmd->flag = cmd->flag->next;
		index += 1;
	}
	while (cmd->content != NULL)
	{
		arg[index] = copy_command(cmd->content->data, &index);
		cmd->content = cmd->content->next;
		index += 1;
	}
	arg[index] = NULL;
	ft_print_2d_array(arg);
}

void	convert_in_3d_array(t_line *all_cmd)
{
	int	i;

	i = 0;
	all_cmd->all_cmd = malloc(sizeof(char **) * (all_cmd->nbr_cmd + 1));
	if (all_cmd->all_cmd == NULL)
		exit (1); //A GERER 
	while (i < all_cmd->nbr_cmd)
	{
		all_cmd->all_cmd[i] = malloc(sizeof(char *) * (count_nbr_element(all_cmd->cmd[i]) + 1));
		if (all_cmd->all_cmd[i] == NULL)
			exit(1); //A GERER
		copy_all_arg(all_cmd->all_cmd[i], &all_cmd->cmd[i]);
		i++;
	}
	all_cmd->all_cmd[i] = NULL;
}
