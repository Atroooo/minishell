/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_3d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:35:51 by neoff             #+#    #+#             */
/*   Updated: 2023/03/17 08:31:04 by vgonnot          ###   ########.fr       */
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

int	copy_list(t_lst *src, char **dest)
{
	int	i;
	int	nbr_element;

	nbr_element = 0;
	while (src != NULL)
	{
		dest[nbr_element] = malloc(sizeof(char) * (ft_strlen(src->data) + 1));
		if (dest[nbr_element] == NULL)
			exit (1); //A GERER PLUS TARD
		nbr_element += 1;
		//ft_strcpy(src->data, dest[nbr_element]); 
		//SEGFAULT IMPOSSIBLE TO MODIFY DEST A CHAR FUNCTION IS NEEDED GRR
		src = src->next;
	}
	return (nbr_element);
}

static char	*copy_command(char *src, int *index)
{
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dest == NULL)
		exit (1);//A GERER PLUS TARD
	ft_strcpy(src, dest);
	*index += 1;
	return (dest);
}

void	copy_all_arg(char **arg, t_cmd *cmd)
{
	int	index;

	index = 0;
	if (cmd->cmd != NULL)
		arg[index] = copy_command(cmd->cmd, &index);
	index += copy_list(cmd->infile, &arg[index]);
	index += copy_list(cmd->outfile, &arg[index]);
	index += copy_list(cmd->flag, &arg[index]);
	index += copy_list(cmd->content, &arg[index]);
	arg[index] = NULL;
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
		//ft_print_2d_array(all_cmd->all_cmd[i]);
		i++;
	}
	all_cmd->all_cmd[i] = NULL;
}
