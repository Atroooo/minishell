/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:33:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/12 14:17:34 by lcompieg         ###   ########.fr       */
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