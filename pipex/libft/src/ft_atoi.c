/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:35:38 by vgonnot           #+#    #+#             */
/*   Updated: 2023/01/10 12:53:16 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	check_sign(const char *sign, int *i)
{
	while ((sign[*i] >= 9 && sign[*i] <= 13) || sign[*i] == 32)
	{
		*i += 1;
	}
	if (sign[*i] == '-')
	{
		*i += 1;
		return (-1);
	}
	if (sign[*i] == '+')
		*i += 1;
	return (1);
}

int	ft_atoi(const char *str)
{
	long long int			result;
	int						negative;
	int						i;

	i = 0;
	result = 0;
	negative = check_sign(&str[i], &i);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result += (str[i] - '0');
		result *= 10;
		i++;
	}
	if (result / 10 * negative > 2147483647)
		return (-1);
	if (result / 10 * negative < -2147483648)
		return (0);
	return (result / 10 * negative);
}
