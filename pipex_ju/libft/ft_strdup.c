/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:08:05 by jmalaval          #+#    #+#             */
/*   Updated: 2025/04/03 10:53:52 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		size;
	int		i;

	size = ft_strlen(s) + 1;
	str = malloc(size * sizeof(char));
	i = 0;
	if (!str)
		return (NULL);
	else
	{
		while (s[i])
		{
			str[i] = s[i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
}
/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char    *s = "bonjour";
	printf("Adresse de s : %p\n", s);
	printf("Contenu de s : %s\n", s);
	printf("Adresse de str apres ft_strdup : %p\n", ft_strdup(s));
	printf("Contenu de str apres ft_strdup : %s\n", ft_strdup(s));
	printf("Adresse de str apres strdup : %p\n", strdup(s));
	printf("Contenu de str apres strdup : %s\n", strdup(s));
}*/
