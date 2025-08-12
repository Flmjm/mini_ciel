/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:17:56 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/04 11:11:02 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
// int main()
// {
//     char src[] = "Hello, World!";
//     char dst[50];
//     // Copier les 6 premiers caractères de src dans dst
//     ft_strlcpy(dst, src, 51);
//     // Afficher la chaîne source et destination
//     printf("Source: %s\n", src);
//     printf("Destination: %s\n", dst);
//     return 0;
// }
