/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:06:24 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/02 15:06:40 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char buffer1[10] = "123456789";
	char buffer2[10] = "123456789";
	int	i;

	i = 0;

	printf("Avant ft_bzero : ");
	while (i < 10)
	{
		printf("[%c]", buffer1[i]);
		i++;
	}
	printf("\n");

	ft_bzero(buffer1, 5);

	i  = 0;
	printf("Après ft_bzero : ");
	while (i < 10)
	{
		printf("[%c]", buffer1[i]);
		i++;
	}
	printf("\n");

	bzero(buffer2, 5);
	i = 0;
	printf("Apres bzero : ");
	while (i < 10)
	{
	printf("[%c]", buffer2[i]);
	i++;
	}
}*/
