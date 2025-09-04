/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:13:04 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/02 15:11:09 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
/*#include <stdio.h>
#include <string.h>

int	main()
{
	char	str1[8] = "bonjour";
	char	str2[8] = "bonjour";

	printf("Avant ft_memset : %s\n", str1);
	printf("Apres ft_memset : %s\n", (char *)ft_memset(str1, 'a', 3));
	printf("Apres memset : %s", (char *)memset(str2, 'a', 3));
}*/
