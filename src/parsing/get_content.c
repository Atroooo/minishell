/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neoff <neoff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:44:42 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/20 15:21:24 by neoff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_content(char *line, t_cmd *cmd)
{
	int		size;
	int		size_malloc;
	char	*content_str;

	size = 0;
	size_malloc = get_size(line, &size);
	content_str = malloc(sizeof(char) * (size_malloc + 1));
	if (content_str == NULL)
		return (-1);
	content_str = copy_cmd(size, line, content_str);
	lst_add_back(&cmd->content, lst_new(content_str));
	return (size);
}
