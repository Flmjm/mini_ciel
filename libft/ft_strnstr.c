/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:29:36 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/08 12:07:41 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	k = ft_strlen(little);
	if (k == 0)
		return ((char *)big);
	if (len < k || len == 0)
		return (NULL);
	while (i < len && big[i])
	{
		j = 0;
		while (little[j] && big[i + j] == little[j])
		{
			if (i + j >= len)
				return (NULL);
			j++;
		}
		if (j == k)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
