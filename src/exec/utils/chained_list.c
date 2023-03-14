/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:19:23 by lcompieg          #+#    #+#             */
/*   Updated: 2023/03/14 13:12:23 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

t_env_var	*ft_lstnew_env(char *name, char *value)
{
	t_env_var	*list;

	list = malloc(sizeof(t_env_var));
	if (list == NULL)
		return (NULL);
	list->name = ft_strdup(name);
    list->value = ft_strdup(value);
    list->next = NULL;
	return (list);
}

void	ft_lstadd_front_env(t_env_var **lst, t_env_var *new)
{
	if (*lst != NULL)
	{
		new->next = *lst;
		(*lst) = new;
	}
	else
		*lst = new;
}

t_env_var	*ft_lstlast_env(t_env_var *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lst_addback_env(t_env_var **lst, t_env_var *new)
{
	if (*lst == NULL)
	{	
		(*lst) = new;
		return ;
	}
	ft_lstlast_env(*lst)->next = new;
}

int	ft_lstsize_env(t_env_var *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
