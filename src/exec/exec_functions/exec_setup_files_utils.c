/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup_files_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:44:34 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/12 15:53:20 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*setup_file(char *raw_file)
{
	char	*file;

	if (!raw_file)
		return (NULL);
	file = ft_strtrim(raw_file, "<> ");
	if (!file)
		return (NULL);
	return (file);
}

int	create_outfiles(t_lst *outfile)
{
	char	*file_name;
	int		c_outfile;

	while (outfile->next != NULL)
	{
		file_name = setup_file(outfile->data);
		c_outfile = open(file_name, O_CREAT, 0644);
		if (c_outfile == -1)
			return (0);
		close(c_outfile);
		free(file_name);
		outfile = outfile->next;
	}
	return (1);
}