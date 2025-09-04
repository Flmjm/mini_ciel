/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:54:33 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/14 11:06:37 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_len(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	if (n <= 9)
		len++;
	if (n == 0)
		return (1);
	return (len);
}

char	*ft_fill_str(char *str, int n, int l)
{
	while (n > 0)
	{
		str[l] = '0' + n % 10;
		n = n / 10;
		l--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len_n;

	len_n = ft_count_len(n);
	str = malloc((len_n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len_n] = '\0';
	len_n--;
	if (n == 0)
		str[len_n] = '0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[len_n] = '8';
			len_n--;
			n = -214748364;
		}
		n = -n;
	}
	ft_fill_str(str, n, len_n);
	return (str);
}

// #include <stdio.h>
// int main()
// {
//     printf("%d\n", ft_count_len(-2147483648));
//     printf("%s", ft_itoa(-2147483648));
// }