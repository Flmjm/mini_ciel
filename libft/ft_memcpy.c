/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:49:59 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/01 17:34:30 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}
// int main()
// {
// 	char src[] = "Hello, World!";
// 	char dest[50];

// 	// Copier les 13 premiers caractères de src dans dest
// 	ft_memcpy(dest, src, 13);

// 	// Afficher la chaîne copiée
// 	printf("Source: %s\n", src);
// 	printf("Destination: %s\n", dest);

// 	return 0;
// }
