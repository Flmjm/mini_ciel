/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:33:17 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/04 16:39:42 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned long	i;
	unsigned int	size_s;

	i = 0;
	if (!s)
		return (NULL);
	size_s = ft_strlen(s);
	if (start > size_s)
		return (ft_strdup(""));
	if (start + len > size_s)
		len = size_s - start;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	else
	{
		while (i < len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
/*
// #include <stdio.h>
// #include <stddef.h>
// int main()
// {
//     const char s[12] = "Hello World";
//     unsigned int start = 5;
//     size_t len = 10;
//     char *str = ft_substr(s, start, len);
//     printf("Chaine originelle : %s\n", s);
//     printf("Nouvelle chaine a partir de %d de %zu caracteres : %s", start,
	len, str);
//     free(str);
// }*/