/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:08:32 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/10 14:26:06 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	ft_bzero(void *s, size_t n)
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
}*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
/*#include <stdio.h>
int	main(void)
{
	size_t  n = -5;
	size_t  s = -5;
	int    *t1 = ft_calloc(n, s);
	int    *t2 = calloc(n, s);
	size_t i = 0;
	while (i < n)
	{
		printf("[%d]", t1[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < n)
	{
		printf("[%d]", t2[i]);
		i++;
	}
	free(t1);
	free(t2);
}*/
