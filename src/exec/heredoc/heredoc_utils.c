/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:33:58 by lcompieg          #+#    #+#             */
/*   Updated: 2023/04/10 11:34:24 by lcompieg         ###   ########.fr       */
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

char	*ft_strnjoin(char *old_dst, char *src, size_t len)
{
	char	*dst;
	size_t	index;
	size_t	j;

	if (src == NULL)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(old_dst) + ft_strlen(src) + 1));
	if (!dst)
		return (free(old_dst), NULL);
	index = 0;
	j = 0;
	while (old_dst && old_dst[index])
	{
		dst[index] = old_dst[index];
		index++;
	}
	while (src[j] && j < len)
	{
		dst[index] = src[j];
		j++;
		index++;
	}
	dst[index] = '\0';
	return (dst);
}
