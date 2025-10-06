/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:41:50 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/03 16:26:14 by mleschev         ###   ########.fr       */
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
// int	main()
// {
// 	printf("%s\n", ft_strrchr("a b c", 'a'));
// 	printf("%s\n", strrchr("a b c", 'a'));
// }
