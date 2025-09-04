/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:08:32 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/07 10:52:35 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long	i;
	unsigned char	*str;
	unsigned char	ch;

	i = 0;
	str = (unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char			str[] = {0, 1, 2, 3, 4, 5};
// 	// char			c = 2 + 256;
// 	// unsigned int	t = 3;
// 	void			*result;

// 	// c = 'u';
// 	// t = 4;
// 	result = ft_memchr(str, 2 + 256, 3);
// 	if (result == NULL)
// 	{
// 		printf("%p\n", ft_memchr(str, 2 + 256, 3));
// 		printf("%p", memchr(str, 2 + 256, 3));
// 	}
// 	else
// 	{
// 		printf("%s\n", (unsigned char *)ft_memchr(str, 2 + 256, 3));
// 		printf("%s", (unsigned char *)memchr(str, 2 + 256, 3));
// 	}
// }
