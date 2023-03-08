/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:05:59 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:53:16 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;

	result = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst != NULL)
	{	
		ft_lstadd_back(&result, ft_lstnew((*f)(lst->content)));
		if (result == NULL)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (result);
}
