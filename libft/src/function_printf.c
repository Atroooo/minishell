/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:13:28 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:47:23 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	checker_int(char c)
{
	if (c == 'c' || c == 'd' || c == 'i' || c == 'u' || c == '%'
		|| c == 'x' || c == 'X' || c == 'p' || c == 's')
	{
		return (1);
	}
	return (0);
}

int	return_value(int i, int nbr_char)
{
	if (i == 0)
		return (0);
	return (i + nbr_char);
}

void	variable_initialization(int *i, int *nbr_char)
{
	*i = 0;
	*nbr_char = 0;
}

int	digit(long int nbr)
{
	int	i;

	i = 1;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}
