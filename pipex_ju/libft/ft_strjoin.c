/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:21:39 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/04 15:17:17 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }
// char	*ft_strdup(const char *s)
// {
// 	char	*str;
// 	int		size;
// 	int		i;

// 	size = ft_strlen(s) + 1;
// 	str = malloc(size * sizeof(char));
// 	i = 0;
// 	if (!str)
// 		return (NULL);
// 	else
// 	{
// 		while (s[i])
// 		{
// 			str[i] = s[i];
// 			i++;
// 		}
// 		str[i] = '\0';
// 		return (str);
// 	}
// }
// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	unsigned long	i;
// 	size_t			len_src;

// 	i = 0;
// 	len_src = ft_strlen(src);
// 	if (len_src < size - 1)
// 		while (i < size - 1)
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 	dst[i] = '\0';
// 	return (ft_strlen(src));
// }
// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	unsigned long	i;
// 	unsigned long	j;
// 	size_t			len_dst;
// 	size_t			len_src;

// 	i = 0;
// 	j = 0;
// 	len_dst = ft_strlen(dst);
// 	len_src = ft_strlen(src);
// 	if (size <= len_dst)
// 		return (size + len_src);
// 	else
// 	{
// 		while (dst[i])
// 			i++;
// 		while (src[j] && (i + j < size - 1))
// 		{
// 			dst[i + j] = src[j];
// 			j++;
// 		}
// 		dst[i + j] = '\0';
// 	}
// 	return (len_dst + len_src);
// }

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len;
	char	*str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, (len + 2));
	ft_strlcat(str, s2, (len + 2));
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char *s1 = "Je suis";
// 	const char *s2 = "";
// 	char *str = ft_strjoin(s1, s2);
// 	printf("Chaine 1 : %s", s1);
// 	printf("Chaine 2 : %s", s2);
// 	printf("Chaine concatenee : %s", str);
// 	free(str);
// }