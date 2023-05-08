/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils_bis                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:39:42 by lcompieg          #+#    #+#             */
/*   Updated: 2023/05/08 15:51:41 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/minishell.h"

static int	set_up_del(int *del, char c)
{
	*del = c;
	return (1);
}

static int	copy_single_char(char *dest, char src, int *y)
{
	dest[*y] = src;
	*y += 1;
	return (1);
}

char	*copy_cmd(int size, char *src, char *dest)
{
	int		i;
	int		del;
	int		y;

	i = 0;
	y = 0;
	del = 0;
	while (i < size)
	{
		if ((src[i] == '\'' || src[i] == '\"') && del == 0)
			i += set_up_del(&del, src[i]);
		else if (del != 0 && src[i] == del)
			i += set_up_del(&del, 0);
		else
			i += copy_single_char(dest, src[i], &y);
	}
	dest[y] = '\0';
	return (dest);
}
