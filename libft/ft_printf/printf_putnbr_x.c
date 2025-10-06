/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putnbr_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:47:52 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/16 23:17:03 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_x(unsigned long nb, const char *base)
{
	int		base_len;
	int		count;

	base_len = 0;
	while (base[base_len])
		base_len++;
	count = 0;
	if (nb >= (unsigned long)base_len)
		count += put_x(nb / base_len, base);
	write(1, &base[nb % base_len], 1);
	count++;
	return (count);
}

int	printf_putnbr_x(int x, const char *base)
{
	unsigned long	nbr;

	nbr = (unsigned int)x;
	return (put_x(nbr, base));
}
