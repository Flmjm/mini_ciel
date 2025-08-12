/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:09:42 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/12 15:19:28 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	n;
	char			*tab;

	n = 0;
	if (!s)
		return (NULL);
	tab = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	tab[ft_strlen(s)] = '\0';
	while (s[n])
	{
		tab[n] = f(n, s[n]);
		n++;
	}
	return (tab);
}
