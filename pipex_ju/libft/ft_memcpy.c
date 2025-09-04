/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:13:39 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/09 17:24:08 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long	i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((void *)d);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char s1[6] = "Hello";
	char s2[6] = "Hello";
	char d1[6];
	char d2[6];

	printf("Avant ft_memcpy : %s\n", s1);
	printf("Apres ft_memcpy : %s\n", (char *)ft_memcpy(d1, s1, 4));
	printf("Apres memcpy : %s\n", (char *)memcpy(d2, s2, 4));
}*/
