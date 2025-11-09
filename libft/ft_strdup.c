/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:13:42 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/08 12:07:28 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	size_t	i;
	char	*array;

	i = ft_strlen(str1);
	array = (char *)ft_malloc((i + 1) * sizeof(char), 0);
	ft_strlcpy(array, str1, i + 1);
	return (array);
}

