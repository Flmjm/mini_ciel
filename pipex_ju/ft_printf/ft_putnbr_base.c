/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:21:11 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/16 14:05:50 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long long n, char *base, unsigned int len)
{
	int	c;

	c = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (n >= len)
		c = c + ft_putnbr_base(n / len, base, len);
	write(1, &base[n % len], 1);
	return (c + 1);
}
