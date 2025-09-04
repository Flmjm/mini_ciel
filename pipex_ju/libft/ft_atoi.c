/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:29:14 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/08 10:18:24 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sign(char c)
{
	int	s;

	s = 1;
	if (c == '-')
		s = -s;
	return (s);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 7 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = ft_sign(nptr[i]);
		i++;
	}
	if (!(ft_isdigit(nptr[i])))
		return (0);
	else
	{
		while (nptr[i] && ft_isdigit(nptr[i]))
		{
			result = result * 10 + (nptr[i] - 48);
			i++;
		}
		return (result * sign);
	}
}
/*#include <stdio.h>
int	main(void)
{
	printf("%d", ft_atoi("-12345"));
}*/
