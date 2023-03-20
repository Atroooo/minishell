/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neoff <neoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:15:32 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/20 15:48:38 by neoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_cmd(char *line, t_cmd *cmd)
{
	int		size;
	int		size_malloc;

	size = 0;
	size_malloc = get_size(line, &size);
	cmd->cmd = malloc(sizeof(char) * (size_malloc + 1));
	if (cmd->cmd == NULL)
		return (-1);
	cmd->cmd = copy_cmd(size, line, cmd->cmd);
	return (size);
}
