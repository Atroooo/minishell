/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:29:57 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/16 07:17:46 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_file(char *line, t_cmd *cmd)
{
	int		size;
	int		size_malloc;
	char	*file_str;

	size = 0;
	size_malloc = get_size(line, &size);
	file_str = malloc(sizeof(char) * (size_malloc + 1));
	if (file_str == NULL)
		exit (1); //A GERER
	file_str = copy_cmd(size, line, file_str);
	if (file_str[0] == '<')
		lst_add_back(&cmd->infile, lst_new(file_str));
	else
		lst_add_back(&cmd->outfile, lst_new(file_str));
	return (size);
}
