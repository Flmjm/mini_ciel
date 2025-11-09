/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:40:37 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/08 12:07:25 by juliette-ma      ###   ########.fr       */
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

