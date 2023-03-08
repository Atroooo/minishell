/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:32:50 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:53:16 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	check_negativ(long int *nbr)
{
	if (*nbr < 0)
	{
		*nbr *= -1;
		return (-1);
	}
	return (1);
}

static void	reverse_tab(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int	size_malloc(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i += 1;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i ++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char				*result;
	long int			nbr;
	int					negativ;
	int					i;

	i = 0;
	nbr = n;
	result = malloc(sizeof(char) * size_malloc(nbr) + 1);
	if (result == NULL)
		return (NULL);
	if (n == 0)
		return (result[0] = '0', result[1] = '\0', result);
	negativ = check_negativ(&nbr);
	while (nbr > 0)
	{
		result[i] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	if (negativ == -1)
		result[i++] = '-';
	result[i] = '\0';
	reverse_tab(result);
	return (result);
}
