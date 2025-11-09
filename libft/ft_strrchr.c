/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:41:50 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/08 12:07:44 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int	i;

	i = ft_strlen(string);
	if (string[i] == (unsigned char)searchedChar)
		return ((char *)(string + i));
	while (i >= 0)
	{
		if (string[i] == (unsigned char)searchedChar)
			return ((char *)(string + i));
		i--;
	}
	return (NULL);
}
