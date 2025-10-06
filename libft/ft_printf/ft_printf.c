/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:43:52 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/25 22:03:36 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	checktype(const char *str, va_list args)
{
	if (*str == 'c')
		return (write(1, (char []){va_arg(args, int)}, 1));
	else if (*str == 's')
		return (printf_putstr(va_arg(args, char *)));
	else if (*str == 'p')
		return (printf_putnbr_p(va_arg(args, void *), "0123456789abcdef"));
	else if (*str == 'd' || *str == 'i')
		return (printf_putnbr_base((long long int)va_arg(args, int),
				"0123456789"));
	else if (*str == 'u')
		return (printf_putnbr_base
			((unsigned long long int)va_arg(args, unsigned int), "0123456789"));
	else if (*str == 'x')
		return (printf_putnbr_x
			((long int)va_arg(args, int), "0123456789abcdef"));
	else if (*str == 'X')
		return (printf_putnbr_x
			((long long int)va_arg(args, int), "0123456789ABCDEF"));
	else if (*str == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += -2 + checktype(&str[i + 1], args);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
	va_end(args);
	return (i + count);
}
