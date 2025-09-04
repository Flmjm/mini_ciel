/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:40:17 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/06 13:31:30 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;
// 	unsigned char	ch;

// 	i = 0;
// 	ch = (unsigned char)c;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if (c == '\0')
// 		return ((char *)&s[i]);
// 	return (NULL);
// }
// int	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }
// char	*ft_substr(const char *s, unsigned int start, size_t len)
// {
// 	char			*str;
// 	unsigned long	i;
// 	unsigned int	size_s;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	size_s = ft_strlen(s);
// 	if (start > size_s)
// 		return (ft_strdup(""));
// 	if (start + len > size_s)
// 		len = size_s - start;
// 	str = malloc((len + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	else
// 	{
// 		while (i < len)
// 		{
// 			str[i] = s[start + i];
// 			i++;
// 		}
// 		str[i] = '\0';
// 	}
// 	return (str);
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

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 && !set)
		return (NULL);
	if (!s1)
		return ((char *)s1);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1);
	while (ft_strchr(set, (int)s1[i]) && s1)
		i++;
	while (j > i && (ft_strchr(set, (int)s1[j])))
		j--;
	str = ft_substr(s1, i, (j - i + 1));
	return (str);
}
// #include <stdio.h>
// int main()
// {
//     const char *s2 = "             Hello";
//     const char *set2 = " ";
//     printf("%s", (char *)ft_strtrim(s2, set2));
// }