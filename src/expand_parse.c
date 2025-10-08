/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:45:37 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/07 15:03:12 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

void	replace_var_input(t_input_info *infos)
{
	int	i;

	i = 0;
	while (infos->input[i])
	{
		while (infos->input[i] == ' ')
			i++;
		if (infos->input[i] == '"')
			i = expand_in_quote(infos, i);
		else if (infos->input[i] == '\'')
			i = next_simple_quote(infos, i);
		if (infos->input[i] == '$')
			expand_var(infos, i, 0);
		i++;
	}
}
int	expand_in_quote(t_input_info *infos, int i)
{
	i++;
	while (infos->input[i] != '"')
	{
		if (infos->input[i] == '"')
			return (i);
		else if (infos->input[i] == '\\' && infos->input[i + 1] == '$')
			erase_in_str(infos, i);
		else if (infos->input[i] == '$')
			expand_var(infos, i, 1);
		i++;
	}
	return (i);
}

void	expand_var(t_input_info *infos, int i, int quote)
{
	char	*temp_input;
    char    env_input[20];
    int     j;

    j = 0;
    i++;
    while (infos->input[i] && infos->input[i] != ' ')
    {
		if (quote)
		{
			if (infos->input[i] == '"')
				break ;
		}
        env_input[j] = infos->input[i];
        i++;
        j++;
    }
    env_input[j] = '\0';
	temp_input = getenv(env_input);
	if (!temp_input)
        return ;
	resize_and_copy(infos, i, j, temp_input);
}

void resize_and_copy(t_input_info *infos, int i, int j, char *temp_input)
{
    char	*buffer;
    int     k;
    int     x;
    int     length;

    x = 0;
    k = 0;

    length = ft_strlen(infos->input) - j + ft_strlen(temp_input) + 1;
    buffer = ft_malloc(sizeof(char) * length, 0);
	while (k < i - j - 1)
    {
        buffer[k] = infos->input[x];
        k++;
        x++;
    }
    x = 0;
    while (x < ft_strlen(temp_input))
    {
        buffer[k] = temp_input[x];
        k++;
        x++;
    }
    while (infos->input[i])
    {
        buffer[k] = infos->input[i];
        k++;
        i++;
    }
    buffer[k] = '\0';
    free(infos->input);
    infos->input = buffer;
}
