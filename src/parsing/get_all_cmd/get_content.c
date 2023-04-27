/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:44:42 by vgonnot           #+#    #+#             */
/*   Updated: 2023/04/27 13:45:43 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

int	get_content(char *line, t_cmd *cmd)
{
	int		size;
	int		size_malloc;
	char	*content_str;

	size = 0;
	size_malloc = get_size(line, &size);
	(void)size_malloc;
	content_str = malloc(sizeof(char) * (size_malloc + 1));
	if (content_str == NULL)
		return (-1);
	content_str = copy_cmd(size, line, content_str);
	if (lst_add_back(&cmd->content, lst_new(content_str)))
	{
		free(content_str);
		return (-1);
	}
	return (size);
}
