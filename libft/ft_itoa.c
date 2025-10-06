/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:21:39 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/23 12:08:16 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reversenb(int n, char *str, size_t nb_len, int sign)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	i = nb_len - 1;
	if (sign < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

static size_t	cntlen(int n)
{
	size_t	cnt_len;
	int		cpy;

	if (n == 0)
		return (1);
	cnt_len = 1;
	cpy = n;
	while (!(cpy < 10))
	{
		cpy = cpy / 10;
		cnt_len++;
	}
	return (cnt_len);
}

static char	*nmin(void)
{
	char	*ff;

	ff = ft_malloc(12 * sizeof(char), 0);
	if (!ff)
		return (NULL);
	ff[0] = '-';
	ff[1] = '2';
	ff[2] = '1';
	ff[3] = '4';
	ff[4] = '7';
	ff[5] = '4';
	ff[6] = '8';
	ff[7] = '3';
	ff[8] = '6';
	ff[9] = '4';
	ff[10] = '8';
	ff[11] = '\0';
	return (ff);
}

char	*ft_itoa(int n)
{
	size_t	cnt_len;
	char	*result;
	int		sign;

	if (n == -2147483648)
		return (nmin());
	cnt_len = 0;
	sign = 1;
	if (n < 0)
	{
		cnt_len++;
		n = n * -1;
		sign = -1;
	}
	cnt_len = cnt_len + cntlen(n);
	result = ft_malloc((cnt_len + 1) * sizeof(char), 0);
	if (!result)
		return (NULL);
	result[cnt_len] = '\0';
	reversenb(n, result, cnt_len, sign);
	return (result);
}
// int	main(void)
// {
// 	printf("%s", ft_itoa(-2147483648));
// }
