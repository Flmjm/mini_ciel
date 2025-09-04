/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:37:23 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/14 15:24:16 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == '%')
			return (1);
		else if (s[i] == '%' && (!ft_strchr("cspdiuxX%", s[i + 1])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_process(char a, va_list args)
{
	if (a == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (a == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (a == 'p')
		return (ft_print_address(va_arg(args, void *)));
	else if ((a == 'd') || (a == 'i'))
		return (ft_print_int(va_arg(args, int)));
	else if (a == 'u')
		return (ft_print_un_int(va_arg(args, unsigned int)));
	else if (a == 'x')
		return (ft_print_x(va_arg(args, int), 'x'));
	else if (a == 'X')
		return (ft_print_x(va_arg(args, int), 'X'));
	else if (a == '%')
		return (write(1, "%", 1));
	else
		return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	argument;
	int		i;
	int		c;

	va_start(argument, s);
	i = 0;
	c = 0;
	if (ft_check(s) == 1)
	{
		while (s[i])
		{
			if (s[i] == '%' && ft_strchr("cspdiuxX%", s[i + 1]))
			{
				c = c + ft_process(s[i + 1], argument);
				i++;
			}
			else
				c = c + (int)write(1, &s[i], 1);
			i++;
		}
	}
	va_end(argument);
	return (c);
}
// #include <stdio.h>

// int	main(void)
// {
// 	char	*ptr;

// 	ptr = "Hello";
// 	ft_printf("Test c : %c %c %c\n", '0', '0', '1');
// 	printf("Test c : %c %c %c\n", '0', '0', '1');
// 	// ft_printf("Test s : %s %s %s\n", "Juliette", "et", "Loulou");
// 	// ft_printf("Test s : %s %s %s\n", "Juliette", "et", "Loulou");
// 	// ft_printf("Test adresse de ptr : %p\n", ptr);
// 	// ft_printf("Test d : %d %d\n", -100, 456162134876);
// 	// ft_printf("Objectif 100%%\n");
// 	// ft_printf("%x\n", 255);
// 	// ft_printf("%X\n", 255);
// }
