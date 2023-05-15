/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:05:32 by atro              #+#    #+#             */
/*   Updated: 2023/05/15 13:44:38 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	print_all_cmd(char ***all_cmd)
{
	int	i;

	i = 0;
	while (all_cmd[i])
	{
		printf("CMD %d\n", i);
		print_tab(all_cmd[i]);
		i++;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf(2, "CMD = |%s|\n", tab[i]);
		i++;
	}
}

void	print_list_delete(t_lst *lst)
{
	while (lst != NULL)
	{
		printf("idx %d idx in line %d %s -> ", \
			lst->index, lst->idx_line, lst->data);
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
	print_list_delete(all_cmd.cmd[i].flag);
	printf("content = ");
	print_list_delete(all_cmd.cmd[i].content);
	printf("infile = ");
	print_list_delete(all_cmd.cmd[i].infile);
	printf("outfile = ");
	print_list_delete(all_cmd.cmd[i].outfile);
}
