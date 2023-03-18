/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:45:07 by vgonnot           #+#    #+#             */
/*   Updated: 2023/02/04 15:52:25 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_strstart(char *str, char *cmpr)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmpr);
	while (cmpr[i] && cmpr[i] == str[i])
		i++;
	if (len == i)
		return (1);
	return (0);
}
