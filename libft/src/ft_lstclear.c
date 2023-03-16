/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 08:24:54 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/15 20:16:33 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		(*del)((*lst)->data);
		current = *lst;
		*lst = (*lst)->next;
		free(current);
	}
}
