/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:05:48 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/08 16:24:25 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

t_env_var	*last_node_case(t_env_var *env_list, \
			t_env_var *new_var, t_env_var	*temp_lst)
{
	temp_lst->next = new_var;
	new_var->next = NULL;
}

t_env_var	*first_node_case(t_env_var *new_var, t_env_var	*temp_lst)
{
	new_var->next = temp_lst;
	return (new_var);
}

t_env_var	*middle_node_case(t_env_var *env_list, t_env_var *prec, \
							t_env_var *new_var, t_env_var	*temp_lst)
{
	prec->next = new_var;
	new_var->next = temp_lst;
	return (env_list);
}

t_env_var	*ft_lst_addsort(t_env_var *env_list, t_env_var *new_var)
{
	t_env_var	*temp_lst;
	t_env_var	*prec;

	temp_lst = env_list;
	prec = NULL;
	if (new_var == NULL)
		return (NULL);
	if (temp_lst == NULL)
		return (new_var);
	while (temp_lst->next != NULL)
	{
		if (ft_strncmp(new_var->name, temp_lst->name, \
			ft_strlen(new_var->name)) < 0)
			break ;
		prec = temp_lst;
		temp_lst = temp_lst->next;
	}
	if (temp_lst->next == NULL)
		env_list = last_node_case(env_list, new_var, temp_lst);
	else if (prec == NULL)
		env_list = first_node_case(new_var, temp_lst);
	else
		env_list = middle_node_case(env_list, prec, new_var, temp_lst);
	return (env_list);
}
