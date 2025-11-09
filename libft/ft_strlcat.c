/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:32:17 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/08 12:07:35 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	j;
	size_t	result_return;

	dest_len = ft_strlen((const char *)dst);
	result_return = dest_len + ft_strlen(src);
	j = 0;
	if (size <= dest_len)
		return (ft_strlen(src) + size);
	while (src[j] && dest_len + j < size - 1)
	{
		*(unsigned char *)(dst + dest_len + j) = *(unsigned char *)(src + j);
		j++;
	}
	dst[dest_len + j] = '\0';
	return (result_return);
}

