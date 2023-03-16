/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_3d_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neoff <neoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:35:51 by neoff             #+#    #+#             */
/*   Updated: 2023/03/16 16:27:41 by neoff            ###   ########.fr       */
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

int	copy_list(char **arg, t_lst *lst)
{
	int	i;
	int	nbr_element;

	nbr_element = 0;
	while (lst != NULL)
	{
		arg[nbr_element] = malloc(sizeof(char) * (ft_strlen(lst->data) + 1));
		if (arg[nbr_element] == NULL)
			exit (1); //A GERER PLUS TARD
		nbr_element += 1;
	}
	return (nbr_element);
}

void	copy_all_arg(char **arg, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd != NULL)
	{
		arg[i] = malloc(sizeof(char) * (ft_strlen(cmd->cmd) + 1));
		if (arg[i] == NULL)
			exit (1);//A GERER PLUS TARD
		ft_strcpy(arg[i], cmd->cmd);
		i += 1;
	}
	i += copy_list(arg[i], cmd->infile);
	i += copy_list(arg[i], cmd->outfile);
	i += copy_list(arg[i], cmd->flag);
	i += copy_list(arg[i], cmd->content);
	arg[i] = NULL;
}

void	convert_in_3d_array(t_line *all_cmd)
{
	int	i;

	i = 0;
	all_cmd->all_cmd = malloc(sizeof(char**) * (all_cmd->nbr_cmd + 1));
	if (all_cmd->all_cmd == NULL)
		exit (1); //A GERER 
	while (i < all_cmd->nbr_cmd)
	{
		all_cmd->all_cmd[i] = malloc(sizeof(char *) * (count_nbr_element(all_cmd->cmd[i]) + 1));
		if (all_cmd->all_cmd[i] == NULL)
			exit(1); //A GERER
		copy_all_arg(all_cmd->all_cmd[i], &all_cmd->cmd[i]);
		ft_print_2d_array(all_cmd->all_cmd[i]);
		i++;
	}
	all_cmd->all_cmd[i] = NULL;
}