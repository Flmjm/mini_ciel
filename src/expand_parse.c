/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:45:37 by root              #+#    #+#             */
/*   Updated: 2025/08/26 22:56:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

void    replace_var_input(t_input_info *infos)
{
    int i;

    i = 0;
    while (infos->input[i])
    {
        while (infos->input[i] == ' ')
            i++;
        if (infos->input[i] == '"')
            i = next_double_quote(infos, i, FALSE); // a remplacer par expand_var_in_double_quote
        else if (infos->input[i] == '\'')
            i = next_simple_quote(infos, i);
        if (infos->input[i] == '$')
            expand_var(infos, i);
        i++;
    }
}

void    expand_var(t_input_info *infos, int i)
{
    char	*buffer;
	char	*temp_input;
    char    env_input[20];
    int     j;
    int     length;
    int     k;
    int     x;

    x = 0;
    k = 0;
    j = 0;
    i++;
    while (infos->input[i] && infos->input[i] != ' ')
    {
        env_input[j] = infos->input[i];
        i++;
        j++;
    }
    env_input[j] = '\0';
	temp_input = getenv(env_input);
	if (!temp_input)
        return ;
    length = ft_strlen(infos->input) - j + ft_strlen(temp_input) + 1;
	buffer = malloc(sizeof(char) * length);
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