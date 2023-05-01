/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:06:19 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/01 13:40:39 by vgonnot          ###   ########.fr       */
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

int	lst_add_back(t_lst **lst, t_lst *new)
{
	if (new == NULL)
		return (-1);
	if (*lst == NULL)
	{	
		(*lst) = new;
		return (0);
	}
	lst_last(*lst)->next = new;
	return (0);
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

t_lst	*lst_new_index(void *content, int index)
{
	t_lst	*list;

	list = malloc(sizeof(t_lst));
	if (list == NULL)
		return (NULL);
	list->data = content;
	list->index = index;
	list->next = NULL;
	return (list);
}

t_lst	*lst_new_double_index(void *content, int index, int index_inline)
{
	t_lst	*list;

	list = malloc(sizeof(t_lst));
	if (list == NULL)
		return (NULL);
	list->data = content;
	list->index = index;
	list->index_inline = index_inline;
	list->next = NULL;
	return (list);
}