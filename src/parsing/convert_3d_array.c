/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_3d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:35:51 by neoff             #+#    #+#             */
/*   Updated: 2023/03/29 17:32:23 by vgonnot          ###   ########.fr       */
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
	return (i);
}

static char	*copy_command(char *src)
{
	char	*dest;

	dest = NULL;
	dest = ft_strcpy(src, dest);
	if (dest == NULL)
		return (NULL);
	return (dest);
}

static int	get_all_command(t_lst *lst, char **arg, int *index)
{
	int		i;

	i = 0;
	while (lst != NULL)
	{
		arg[i] = copy_command(lst->data);
		if (arg[i] == NULL)
			return (-1);
		lst = lst->next;
		*index += 1;
		i++;
	}
	return (0);
}

static int	get_single_command(char *src, char **dest, int *index)
{
	if (src == NULL)
		return (0);
	*dest = copy_command(src);
	if (*dest == NULL)
		return (-1);
	*index += 1;
	return (0);
}

int	list_copy(t_lst **dest, t_lst *src)
{
	char	*str;

	str = ft_strdup(src->data);
	if (str == NULL)
		return (1);
	if (lst_add_back(dest, lst_new(str)))
		return (1);
	return (0);
}

t_lst	*free_and_get_next(t_lst *lst)
{
	t_lst	*prec;

	prec = lst;
	lst = lst->next;
	free(prec->data);
	free(prec);
	return (lst);
}

int	get_all_files(t_cmd *cmd, t_line *all_cmd)
{
	while (cmd->infile != NULL)
	{
		if (list_copy(&all_cmd->infile, cmd->infile))
			return (1);
		cmd->infile = free_and_get_next(cmd->infile);
	}
	while (cmd->outfile != NULL)
	{
		if (list_copy(&all_cmd->outfile, cmd->outfile))
			return (1);
		cmd->outfile = free_and_get_next(cmd->outfile);
	}
	return (0);
}

int	copy_all_arg(char **arg, t_cmd *cmd)
{
	int	index;

	index = 0;
	if (get_single_command(cmd->cmd, &arg[index], &index))
		return (-1);
	if (get_all_command(cmd->flag, &arg[index], &index))
		return (-1);
	if (get_all_command(cmd->content, &arg[index], &index))
		return (-1);
	arg[index] = NULL;
	return (0);
}

int	convert_in_3d_array(t_line *all_cmd)
{
	int	i;

	i = 0;
	all_cmd->all_cmd = malloc(sizeof(char **) * (all_cmd->nbr_cmd + 1));
	if (all_cmd->all_cmd == NULL)
		return (-1);
	all_cmd->infile = NULL;
	all_cmd->outfile = NULL;
	while (i < all_cmd->nbr_cmd)
	{
		all_cmd->all_cmd[i] = malloc(sizeof(char *) * (count_nbr_element(all_cmd->cmd[i]) + 1));
		if (all_cmd->all_cmd[i] == NULL)
			return (-1);
		if (copy_all_arg(all_cmd->all_cmd[i], &all_cmd->cmd[i]))
			return (-1);
		if (get_all_files(&all_cmd->cmd[i], all_cmd))
			return (-1);
		i++;
	}
	print_list_delete(all_cmd->infile);
	print_list_delete(all_cmd->outfile);
	all_cmd->all_cmd[i] = NULL;
	return (1);
}
