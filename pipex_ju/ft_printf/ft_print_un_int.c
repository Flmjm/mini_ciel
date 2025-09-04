/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_un_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:14:40 by jmalaval          #+#    #+#             */
/*   Updated: 2025/06/18 11:26:54 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_len(unsigned int n)
{
	int	len;

	len = 0;
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

static char	*ft_uitoa(unsigned int n)
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
	while (n > 0)
	{
		str[len_n] = '0' + n % 10;
		n = n / 10;
		len_n--;
	}
	return (str);
}

int	ft_print_un_int(unsigned int i)
{
	char	*str;
	int		len;

	str = ft_uitoa(i);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
