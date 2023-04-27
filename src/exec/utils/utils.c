/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:07:49 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/26 18:02:36 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	cmd_size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	get_total_cmd(t_line *all_cmd)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (all_cmd->all_cmd[i])
	{
		j = 0;
		while (all_cmd->all_cmd[i][j])
		{
			count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	ft_lstsize_file(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	print_unset_error(char *cmd, int s)
{
	if (s == 0)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	if (s == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": event not found", 2);
		return ;
	}
}
