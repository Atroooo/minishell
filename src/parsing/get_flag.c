/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:27:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/20 09:47:57 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_flag(char *line, t_cmd *cmd, t_line *all_cmd)
{
	int		size;
	int		size_malloc;
	char	*flag_str;

	size = 0;
	size_malloc = get_size(line, &size);
	flag_str = malloc(sizeof(char) * (size_malloc + 1));
	if (flag_str == NULL)
		quit_function_parsing(all_cmd);
	flag_str = copy_cmd(size, line, flag_str);
	lst_add_back(&cmd->flag, lst_new(flag_str));
	return (size);
}
