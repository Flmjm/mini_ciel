/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:20:49 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/23 12:03:01 by mleschev         ###   ########.fr       */
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
// int main() {
//     int i;
//     int * pointer = (int *) calloc( 10, sizeof(int) );
//     for (i=0; i<10; i++ ) {
//         printf( "%d ", pointer[i] );
//     }
//     printf( "\n" );
//     /* On libère le bloc de mémoire alloué dynamiquement */
//     free( pointer );
//     return 0;
// }
