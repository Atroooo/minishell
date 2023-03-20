/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:15:32 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/20 09:50:17 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_cmd(char *line, int *no_command, t_cmd *cmd, t_line *all_cmd)
{
	int		size;
	int		size_malloc;

	*no_command = FALSE;
	size = 0;
	size_malloc = get_size(line, &size);
	cmd->cmd = malloc(sizeof(char) * (size_malloc + 1));
	if (cmd->cmd == NULL)
		quit_function_parsing(all_cmd);
	cmd->cmd = copy_cmd(size, line, cmd->cmd);
	return (size);
}
