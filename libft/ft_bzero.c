/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:30:14 by mleschev          #+#    #+#             */
/*   Updated: 2025/03/31 13:49:04 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = ptr;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
/*
int main() {
    char buffer[10];
    
    // Afficher le contenu initial du buffer
    printf("Avant ft_bzero: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    
    // Appeler ft_bzero pour remplir le buffer de zéros
    ft_bzero(buffer, sizeof(buffer));
    
    // Afficher le contenu du buffer après ft_bzero
    printf("Après ft_bzero: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", buffer[i]);  // Devrait afficher des zéros
    }
    printf("\n");

    return 0;
}*/
