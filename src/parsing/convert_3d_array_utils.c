/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_3d_array_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:45:01 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/04 13:48:50 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	list_copy(t_lst **dest, t_lst *src, int index, int index_inline)
{
	char	*str;

	str = ft_strdup(src->data);
	if (str == NULL)
		return (1);
	if (lst_add_back(dest, lst_new_double_index(str, index, index_inline)))
	{
		free(str);
		return (1);
	}
	return (0);
}

static char	*copy_command(char *src)
{
	char	*dest;

	dest = NULL;
	dest = ft_strcpy(src, dest);
	if (dest == NULL)
		return (NULL);
	return (dest);
}

static int	get_all_command(t_lst *lst, char **arg, int *index)
{
	int		i;
	t_lst	*temp;

	i = 0;
	while (lst != NULL)
	{
		if (lst->data != NULL || lst->data[0] == '\0')
		{
			arg[i] = copy_command(lst->data);
			if (arg[i] == NULL)
				return (-1);
			*index += 1;
			i++;
		}
		temp = lst->next;
		lst = temp;
	}
	return (0);
}

static int	get_single_command(char *src, char **dest, int *index)
{
	if (src == NULL)
		return (0);
	*dest = copy_command(src);
	if (*dest == NULL)
		return (-1);
	*index += 1;
	return (0);
}

int	copy_all_arg(char **arg, t_cmd *cmd)
{
	int	index;

	index = 0;
	if (get_single_command(cmd->cmd, &arg[index], &index))
		return (-1);
	if (get_all_command(cmd->flag, &arg[index], &index))
		return (-1);
	if (get_all_command(cmd->content, &arg[index], &index))
		return (-1);
	arg[index] = NULL;
	return (0);
}
