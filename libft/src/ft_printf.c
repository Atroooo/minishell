/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgonnot <vgonnot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:52:49 by vgonnot           #+#    #+#             */
/*   Updated: 2023/05/15 13:58:10 by vgonnot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	print(const char c, long int nbr, int *i, int fd)
{
	int	temp;

	if (c == 'd' || c == 'i')
		return (*i += 2, ft_putnbr_fd((int)nbr, fd), digit(nbr));
	else if (c == 'c')
		return (*i += 2, ft_putchar_fd((int)nbr, fd), 1);
	else if (c == 'u')
	{
		*i += 2;
		return (ft_putnbr_fd((unsigned int)nbr, fd), digit((unsigned int)nbr));
	}
	else if (c == '%')
		return (*i += 2, ft_putchar_fd('%', fd), 1);
	else if (c == 'x' || c == 'X' || c == 'p')
	{
		temp = hexadecimal_conversion(c, nbr, fd);
		if (temp == -100)
			return (-100);
		return (*i += 2, temp);
	}
	return (0);
}

static int	print_char(char *str, int *i, int fd)
{
	*i += 2;
	if (str == NULL)
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

static int	char_parse(char c, int *i, va_list ap, int fd)
{
	int	temp;

	temp = 0;
	if (c == 'p')
		temp = print(c, va_arg(ap, unsigned long), i, fd);
	else if (c == '%')
		temp = print(c, 0, i, fd);
	else
		temp = print(c, va_arg(ap, int), i, fd);
	if (temp == -100)
		return (-100);
	return (temp);
}

static int	check_after_percentage(const char *str, int fd, int *i, va_list ap)
{
	int	temp;

	temp = 0;
	if (str[0] == '%' && str[1] == 's')
		temp += print_char(va_arg(ap, char *), &*i, fd);
	else if (str[0] == '%' && checker_int(str[1]) == 1)
	{
		temp = char_parse(str[1], &*i, ap, fd);
		if (temp == -100)
			return (-100);
	}
	else if (str[0] == '%')
	{
		*i += 1;
		return (temp - 1);
	}
	return (temp - 2);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	ap;
	int		i;
	int		nbr_char;
	int		temp;

	va_start(ap, str);
	if (write(fd, 0, 0) != 0)
		return (-1);
	variable_initialization(&i, &nbr_char);
	while (str[i] != '\0')
	{
		while (str[i] == '%')
		{
			temp = check_after_percentage(&str[i], fd, &i, ap);
			if (temp == -100)
				return (-1);
			nbr_char += temp;
		}
		if (str[i] == '\0')
			return (i + nbr_char);
		if (!(str[i] == '%' && checker_int(str[i + 1]) == 1))
			ft_putchar_fd(str[i++], fd);
	}
	va_end(ap);
	return (return_value(i, nbr_char));
}
