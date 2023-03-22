/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neoff <neoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:27:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/22 15:01:08 by neoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
	lst_add_back(&cmd->flag, lst_new(flag_str));
	return (size);
}
