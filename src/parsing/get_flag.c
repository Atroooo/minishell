/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:27:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/03/16 07:17:46 by vgonnot          ###   ########.fr       */
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
		exit (1); //A GERER
	flag_str = copy_cmd(size, line, flag_str);
	lst_add_back(&cmd->flag, lst_new(flag_str));
	printf("%s\n", cmd->flag->data);
	return (size);
}
