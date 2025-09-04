/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:09:19 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/16 14:08:28 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_x(unsigned int n, int x)
{
	int				c;
	unsigned char	ch;

	c = 0;
	ch = (unsigned char)x;
	if (ch == 'X')
		c = ft_putnbr_base(n, "0123456789ABCDEF", 16);
	else if (ch == 'x')
		c = ft_putnbr_base(n, "0123456789abcdef", 16);
	return (c);
}
