/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:27:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/27 13:47:23 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	get_flag(char *line, t_cmd *cmd)
{
	int		size;
	int		size_malloc;
	char	*flag_str;

	size = 0;
	size_malloc = get_size(line, &size);
	flag_str = malloc(sizeof(char) * (size_malloc + 1));
	if (flag_str == NULL)
		return (-1);
	flag_str = copy_cmd(size, line, flag_str);
	if (lst_add_back(&cmd->flag, lst_new(flag_str)))
		return (-1);
	return (size);
}
