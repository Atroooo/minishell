/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_similar_variable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:14:05 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/08 11:06:04 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static void	free_node(t_env_var *lst)
{
	free(lst->name);
	free(lst->value);
	free(lst);
}

static void	check_last_node(t_env_var *lst, t_env_var *prec, char *name)
{
	if (lst && ft_strcmp(lst->name, name) == 0)
	{
		free_node(lst);
		prec->next = NULL;
	}
}

static void	remove_variable( \
			t_env_var *lst, t_env_var *prec, t_env_var *next)
{
	free_node(lst);
	prec->next = next;
	lst = prec;
}

t_env_var	*remove_similar_variable(char *name, t_env_var *lst)
{
	t_env_var	*prec;
	t_env_var	*next;
	t_env_var	*lst_save;

	if (lst == NULL)
		return (lst);
	next = lst->next;
	lst_save = lst;
	if (ft_strcmp(lst->name, name) == 0)
		return (free_node(lst), next);
	while (lst->next != NULL)
	{
		prec = lst;
		lst = lst->next;
		next = lst->next;
		if (ft_strcmp(lst->name, name) == 0)
			return (remove_variable(lst, prec, next), lst_save);
	}
	check_last_node(lst, prec, name);
	return (lst_save);
}
