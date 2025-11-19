/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:43:13 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/08 12:07:49 by juliette-ma      ###   ########.fr       */
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
	array = (char *)ft_malloc((len + 1) * sizeof(char), 0);
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
