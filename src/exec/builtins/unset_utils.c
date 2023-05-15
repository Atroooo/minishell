/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:50:43 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 15:08:33 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_unset_error(char *cmd)
{
	g_status = 1;
	ft_printf(2, "unset: `%s': not a valid identifier\n", cmd);
	return ;
}

static void	free_node(t_env_var *delete)
{
	free(delete->name);
	free(delete->value);
	free(delete);
}

t_env_var	*delete_first_node(t_env_var *env_list)
{
	t_env_var	*delete;

	delete = env_list;
	env_list = env_list->next;
	free_node(delete);
	return (env_list);
}

t_env_var	*delete_middle_node( \
	t_env_var *env_list, t_env_var *temp, int i)
{
	t_env_var	*delete;
	t_env_var	*prev;

	prev = get_prev(env_list, i - 1);
	if (!prev->next)
		return (temp);
	delete = prev->next;
	prev->next = delete->next;
	free_node(delete);
	delete = NULL;
	return (temp);
}

t_env_var	*delete_node(t_env_var *env_list, int i)
{
	t_env_var	*temp;

	temp = env_list;
	if (i == 0)
		return (delete_first_node(env_list));
	else
		return (delete_middle_node(env_list, temp, i));
}
