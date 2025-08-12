/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:58:17 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/02 11:41:48 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( const char *string, int searchedChar )
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == (unsigned char)searchedChar)
			return ((char *)(string + i));
		i++;
	}
	if (string[i] == (unsigned char)searchedChar)
		return ((char *)(string + i));
	return (NULL);
}
