/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putnbr_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:12:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/16 23:16:51 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	putbase(unsigned long long nb, const char *base)
{
	int		base_len;
	int		count;

	base_len = 0;
	while (base[base_len])
		base_len++;
	count = 0;
	if (nb >= (unsigned long long)base_len)
		count += putbase(nb / base_len, base);
	write(1, &base[nb % base_len], 1);
	count++;
	return (count);
}

int	printf_putnbr_base(long long nbr, const char *base)
{
	int	sign;

	sign = 0;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		write(1, "-", 1);
		sign++;
	}
	return (putbase(nbr, base) + sign);
}

int	printf_putnbr_p(void *p, const char *base)
{
	unsigned long long	nbr;

	if (!p)
		return (write(1, "(nil)", 5));
	nbr = (unsigned long long)p;
	return (printf_putstr("0x") + putbase(nbr, base));
}
