/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:01:11 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/04 11:11:45 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (NULL);
	while (i < size)
	{
		if (*(unsigned char *)(memoryBlock + i) == (unsigned char)searchedChar)
			return ((void *)(memoryBlock + i));
		i++;
	}
	return (NULL);
}
