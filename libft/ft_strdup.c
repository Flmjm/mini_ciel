/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:13:42 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/23 12:08:33 by mleschev         ###   ########.fr       */
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
// int	main()
// {
// 	char	aled[] = "oskour    aled";
// 	printf("%s\n", ft_strdup(aled));
// 	printf("%s\n", strdup(aled));

// }
