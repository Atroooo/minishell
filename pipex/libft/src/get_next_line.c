/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 08:50:44 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/20 16:32:13 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*buffer_parsing(char *old_dest, char *buffer, int *size_dest)
{
	int		i;
	char	*dest;

	i = 1;
	while (buffer[i] != '\0' && buffer[i - 1] != '\n')
		i++;
	if (buffer[0] == '\n')
		i = 1;
	dest = ft_strjoin_c(old_dest, buffer, i, &*size_dest);
	if (dest == NULL)
		return (NULL);
	buffer = delete_substring(buffer, &buffer[i]);
	return (dest);
}

static char	*return_valu(char *final_str, int size_dest, char *buffer)
{
	if (final_str[size_dest - 1] == '\n' || final_str[size_dest] == '\0')
		return (final_str);
	free(final_str);
	buffer[0] = 0;
	return (NULL);
}

static int	check_if_return(char *final_str, int size_dest)
{
	if (final_str == NULL)
		return (1);
	if (final_str[size_dest - 1] == '\n')
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	int			byte;
	static char	buffer[BUFFER_SIZE + 1];
	char		*final_str;
	int			size_dest;

	if (read(fd, NULL, 0) == -1)
		return (buffer[0] = 0, NULL);
	final_str = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (buffer[0] = 0, NULL);
	if (buffer[0] != '\0')
	{
		final_str = buffer_parsing(final_str, buffer, &size_dest);
		if (check_if_return(final_str, size_dest))
			return (return_valu(final_str, size_dest, buffer));
	}
	byte = read(fd, buffer, BUFFER_SIZE);
	while (byte)
	{
		final_str = buffer_parsing(final_str, buffer, &size_dest);
		if (check_if_return(final_str, size_dest))
			return (return_valu(final_str, size_dest, buffer));
		byte = read(fd, buffer, BUFFER_SIZE);
	}
	return (ft_memset_c(buffer, 0, BUFFER_SIZE +1), final_str);
}
