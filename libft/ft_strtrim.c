/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:56:12 by mleschev          #+#    #+#             */
/*   Updated: 2025/04/05 14:36:36 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy(char *tab, char const *s, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (start + i < end)
	{
		tab[i] = s[start + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static int	findstart(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	check;

	i = 0;
	check = 0;
	while (i < (size_t)ft_strlen(set))
	{
		j = 0;
		while (j < (size_t)ft_strlen(s1))
		{
			if (s1[j] == set[i] && j == check)
			{
				check++;
				j = 0;
				i = 0;
			}
			j++;
		}
		i++;
	}
	return (check);
}

static int	findend(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	check;

	i = 0;
	check = (size_t)ft_strlen(s1) - 1;
	while (i < (size_t)ft_strlen(set))
	{
		j = ft_strlen(s1);
		while (j > 0)
		{
			if (s1[j] == set[i] && j == check)
			{
				check--;
				j = ft_strlen(s1);
				i = 0;
			}
			j--;
		}
		i++;
	}
	return (check);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1)
		return (NULL);
	if (!set)
	{
		start = 0;
		end = ft_strlen(s1);
	}
	else
	{
		start = findstart(s1, set);
		if (start >= (size_t)ft_strlen(s1))
			return (ft_strdup(""));
		end = findend(s1, set) + 1;
	}
	result = malloc((end - start + 1) * sizeof(char));
	if (!result)
		return (NULL);
	copy(result, s1, start, end);
	return (result);
}
// int	main(void)
// {
// 	char	aled[] = "rrsroskorurorro";
// 	char	set[] = "or";
// 	printf("%s", ft_strtrim(aled, set));
// }
