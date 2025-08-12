/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:32:17 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/02 14:50:36 by mleschev         ###   ########.fr       */
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
// int main() {
//     // Définition des chaînes pour le test
//     char dest1[50] = "Hello, ";
//     char src1[] = "World!";
//     char dest2[50] = "Hello, ";
//     char src2[] = "World!";
//     size_t size = 50; // Taille maximale de dest
//     // Affichage avant appel à ft_strlcat
//     printf("Avant ft_strlcat: \n");
//     printf("dest1: \"%s\"\n", dest1);
//     printf("src1: \"%s\"\n", src1);
//     // Test avec ft_strlcat
//     size_t result1 = ft_strlcat(dest1, src1, size);
//     // Affichage après appel à ft_strlcat
//     printf("Après ft_strlcat: \n");
//     printf("dest1: \"%s\"\n", dest1);
//     printf("Résultat: %zu\n", result1);
// }
