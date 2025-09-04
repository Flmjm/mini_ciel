/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:25:52 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/11 16:59:57 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *str, char c1)
{
	int	i;
	int	w;

	if (!str || str[0] == '\0')
		return (0);
	if (!ft_isprint(c1) && str)
		return (1);
	i = 0;
	w = 1;
	while (str[i] == c1)
		i++;
	while (str[i])
	{
		if ((str[i] == c1) && (str[i - 1] != c1))
			w++;
		i++;
	}
	if (str[i - 1] == c1)
		return (w - 1);
	else
		return (w);
}

static char	**ft_fill_tab(char **tab, const char *str, char c, int w)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	x = 0;
	while (x < w)
	{
		while (str[i] && str[i] == c)
			i++;
		j = i;
		while (str[j] && str[j] != c)
			j++;
		tab[x] = (ft_substr(str, i, (j - i)));
		if (!tab[x])
			free(tab[x]);
		i = j;
		x++;
	}
	tab[x] = NULL;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	int		w;
	int		x;
	char	**tab;

	if (!s)
		return (NULL);
	x = 0;
	w = ft_countwords(s, c);
	tab = malloc((w + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	if (w == 0)
	{
		tab[x] = NULL;
		return (tab);
	}
	ft_fill_tab(tab, s, c, w);
	return (tab);
}
