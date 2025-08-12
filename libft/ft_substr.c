/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:43:13 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/05 02:06:03 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len )
{
	char	*array;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start)
		return (ft_strdup(""));
	if ((int)len > ft_strlen(s) - (int)start)
		len = (size_t)ft_strlen(s) - (size_t)start;
	array = (char *)malloc((len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	array[len] = '\0';
	while (i < len && *(char *)(s + start + i))
	{
		array[i] = *(char *)(s + start + i);
		i++;
	}
	return (array);
}
// int	main()
// {
// 	printf("%s\n", ft_substr("0123456789", 9, 10));
// }
