/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:40:37 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/23 12:03:29 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cntwrd(const char *str, char sep)
{
	int	i;
	int	wrd;

	wrd = 0;
	i = 0;
	while (str[i] && str[i] == sep)
		i++;
	while (str[i])
	{
		if (i == 0 && str[i] != sep)
			wrd++;
		if (i > 0 && str[i - 1] == sep && str[i] != sep)
			wrd++;
		i++;
	}
	return (wrd);
}

static int	wrdlen(const char *str, char sep, int wrdnb)
{
	int	i;
	int	wrd;
	int	wrd_len;

	wrd = 0;
	i = 0;
	wrd_len = 0;
	while (str[i] && str[i] == sep)
		i++;
	while (str[i])
	{
		if (i == 0 && str[i] != sep)
			wrd++;
		if (i > 0 && str[i - 1] == sep && str[i] != sep)
			wrd++;
		if (wrd == wrdnb && str[i] != sep)
			wrd_len++;
		i++;
	}
	return (wrd_len);
}

static void	cpywrd(char *tab, char const *str, char sep, int wrdnb)
{
	int	i;
	int	wrd;
	int	j;

	j = 0;
	wrd = 0;
	i = 0;
	while (str[i] && str[i] == sep)
		i++;
	while (str[i])
	{
		if (i == 0 && str[i] != sep)
			wrd++;
		if (i > 0 && str[i - 1] == sep && str[i] != sep)
			wrd++;
		if (wrd == wrdnb && str[i] != sep)
			tab[j++] = str[i];
		i++;
	}
	tab[j] = '\0';
}

static void	freearray(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	count = cntwrd(s, c);
	array = ft_malloc((count + 1) * sizeof(char *), 0);
	if (!array)
		return (NULL);
	array[count] = NULL;
	i = -1;
	while (++i < count)
	{
		array[i] = ft_malloc((wrdlen(s, c, i + 1) + 1) * sizeof(char), 0);
		if (!array[i])
			return (freearray(array, i), NULL);
		cpywrd(array[i], s, c, i + 1);
	}
	return (array);
}

// int	main(void)
// {
// 	int		i;
// 	char	string[] = "Je suis un split simple";
// 	char	c;
// 	char	**dest;

// 	i = 0;
// 	// char	test[] = "                            ";
// 	c = ' ';
// 	dest = ft_split(string, c);
// 	while (dest)
// 	{
// 		printf("%s", dest[i]);
// 		i++;
// 	}
// 	// char **dest = ft_malloc(2 * sizeof(char *));
// 	// dest[1] = NULL;
// 	// dest[0] = ft_malloc((2));
// 	// dest[0][0] = clc( string, c, 0+1, 0);
// 	// printf("%c", dest[0][0]);
// 	// 	dest = ft_split(string, c);
// 	// 	while (dest != NULL)
// 	// 	{
// 	// 		printf("%s", dest[i]);
// 	// 		i++;
// 	// 	}
// 	// 	free (dest);
// }
