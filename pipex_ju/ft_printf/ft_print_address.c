/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:44:07 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/16 14:12:08 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_address(void *ptr)
{
	long long	add;
	int			c;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	add = (long long)ptr;
	ft_putstr_fd("0x", 1);
	c = 2 + ft_putnbr_base((unsigned long long)add, "0123456789abcdef", 16);
	return (c);
}
