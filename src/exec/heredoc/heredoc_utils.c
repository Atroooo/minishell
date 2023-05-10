/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:50:53 by marvin            #+#    #+#             */
/*   Updated: 2023/05/03 17:50:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

char	*get_delimiter(char *str)
{
	char	*delimiter;

	delimiter = ft_strtrim(str, "< ");
	if (!delimiter)
		return (NULL);
	return (delimiter);
}

char	*get_delimiter_hdoc(t_line *all_cmd, int hdoc_count)
{
	t_lst	*last_hdoc;
	char	*hdoc;
	int		i;

	last_hdoc = all_cmd->infile;
	i = 0;
	while (last_hdoc)
	{
		if (ft_strnstr(last_hdoc->data, "<<", 2) != NULL)
		{
			hdoc = last_hdoc->data;
			i++;
		}
		if (hdoc_count == i)
			break ;
		last_hdoc = last_hdoc->next;
	}
	return (hdoc);
}

int	get_nbr_hdoc(t_line *all_cmd)
{
	t_lst	*temp_hdoc;
	int		count;

	temp_hdoc = all_cmd->infile;
	count = 0;
	while (temp_hdoc)
	{
		if (ft_strnstr(temp_hdoc->data, "<<", 2) != NULL)
			count++;
		temp_hdoc = temp_hdoc->next;
	}
	return (count);
}
