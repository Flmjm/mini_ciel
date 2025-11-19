/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:13:42 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/16 23:07:22 by manu             ###   ########.fr       */
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
