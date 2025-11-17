/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:20:49 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/16 23:03:24 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*array;

	if (size != 0 && num > ((size_t) -1 / size))
		return (NULL);
	array = ft_malloc(num * size, 0);
	if (array == NULL)
		return (NULL);
	ft_memset(array, 0, num * size);
	return (array);
}
