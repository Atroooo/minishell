/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:06:19 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/16 08:22:25 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lst	*lst_last(t_lst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	lst_add_back(t_lst **lst, t_lst *new)
{
	if (*lst == NULL)
	{	
		(*lst) = new;
		return ;
	}
	lst_last(*lst)->next = new;
}

t_lst	*lst_new(void *content)
{
	t_lst	*list;

	list = malloc(sizeof(t_lst));
	if (list == NULL)
		return (NULL);
	list->data = content;
	list->next = NULL;
	return (list);
}

void	print_list(t_lst *lst)
{
	while (lst != NULL)
	{
		printf("%s -> ", lst->data);
		lst = lst->next;
	}
	printf("NULL\n");
}

void	print_cmd(int i, t_line all_cmd)
{
	printf("cmd = ");
	if (all_cmd.cmd[i].cmd == NULL)
		printf("NULL");
	else
		printf("%s\n", all_cmd.cmd[i].cmd);
	printf("flag = ");
	print_list(all_cmd.cmd[i].flag);
	printf("content = ");
	print_list(all_cmd.cmd[i].content);
	printf("infile = ");
	print_list(all_cmd.cmd[i].infile);
	printf("outfile = ");
	print_list(all_cmd.cmd[i].outfile);
}
