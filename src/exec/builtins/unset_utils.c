/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:50:43 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/15 14:12:20 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

void	print_unset_error(char *cmd, int s)
{
	g_status = 1;
	if (s == 0)
	{
		ft_printf(2, "export; `%s': not a valid identifier\n", cmd);
		return ;
	}
	if (s == 1)
	{
		ft_printf(2, "%s: event not found\n");
		return ;
	}
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
