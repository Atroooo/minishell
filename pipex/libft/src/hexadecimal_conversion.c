/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexadecimal_conversion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:00:20 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:47:34 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	size(unsigned long nbr, char c)
{
	int			i;

	i = 1;
	if (nbr == 0)
		i = 2;
	while (nbr > 0)
	{
		nbr /= 16;
		i++;
	}
	if (c == 'p')
		i += 2;
	return (i);
}

static int	convert(char c, unsigned long nbr, char *hexadecimal_str, int i)
{
	int	temp;

	while (nbr > 0)
	{
		temp = nbr % 16;
		nbr /= 16;
		if (c == 'X')
		{
			if (temp > 9)
				hexadecimal_str[i] = 'A' + temp - 10;
			else
				hexadecimal_str[i] = '0' + temp;
		}
		else
		{
			if (temp > 9)
				hexadecimal_str[i] = 'a' + temp - 10;
			else
				hexadecimal_str[i] = '0' + temp;
		}
		i++;
	}
	hexadecimal_str[i] = '\0';
	return (i);
}

static void	reverse_tab(int len, char *str, char c)
{
	int		i;
	char	temp;

	len -= 1;
	i = 0;
	if (c == 'p')
		i += 2;
	while (i < len)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
		i++;
		len--;
	}
}

int	hexadecimal_conversion(char c, unsigned long nbr)
{
	char	*hexadecimal_str;
	int		i;
	int		len;

	i = 0;
	hexadecimal_str = malloc(sizeof(char) * (size(nbr, c)));
	if (hexadecimal_str == NULL)
		return (-100);
	if (c == 'p')
	{
		hexadecimal_str[i++] = '0';
		hexadecimal_str[i++] = 'x';
		if (nbr == 0)
			hexadecimal_str[i++] = '0';
		i = convert(c, nbr, hexadecimal_str, i++);
	}
	else
	{
		if (nbr == 0)
			hexadecimal_str[i++] = '0';
		i = convert(c, (unsigned int)nbr, hexadecimal_str, i);
	}
	return (reverse_tab(i, hexadecimal_str, c), ft_putstr_fd(hexadecimal_str, 1)
		, len = ft_strlen(hexadecimal_str), free(hexadecimal_str), len);
}
