/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:45:37 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/10 14:31:29 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

void	erase_in_str(t_input_info *infos, int i)
{
	char *buffer;
	int	j;
	j = 0;

	buffer = ft_malloc(sizeof(char) * (ft_strlen(infos->input) + 1), 0);
	if (!buffer)
		return;
	while (j < i)
	{
		buffer[j] = infos->input[j];
		j++;
	}
	while (infos->input[i])
	{
		buffer[j] = infos->input[i + 1];
		j++;
		i++;
	}
	buffer[j] = '\0';
	infos->input = buffer;
}

void	 replace_var_input(t_input_info *infos, t_exitcode *exit_code)
{
	int	i;

	i = 0;
	while (infos->input[i])
	{
		while (infos->input[i] && infos->input[i] == ' ')
			i++;
		if (infos->input[i] == '"')
			i = expand_in_quote(infos, i, exit_code);
		else if (infos->input[i] == '\'')
			i = next_simple_quote(infos, i, FALSE);
		else if (infos->input[i] == '$' && infos->input[i + 1]
			&& (ft_isalnum(infos->input[i + 1]) || infos->input[i + 1] == '_' || infos->input[i + 1] == '?'))
			expand_var(infos, i, 0, exit_code);
		else if (infos->input[i])
			i++;
		if (i >= ft_strlen(infos->input))
			break;
	}
}
int	expand_in_quote(t_input_info *infos, int i, t_exitcode *exit_code)
{
	i++;
	while (infos->input[i] && infos->input[i] != '"')
	{
		if (infos->input[i] == '\'' && infos->input[i + 1] && infos->input[i + 2] == '\'')
			i += 3;
		else if (infos->input[i] == '\\' && infos->input[i + 1] == '$')
			erase_in_str(infos, i);
		else if (infos->input[i] == '$' && infos->input[i + 1]
			&& (ft_isalnum(infos->input[i + 1]) || infos->input[i + 1] == '_' || infos->input[i + 1] == '?'))
			expand_var(infos, i, 1, exit_code);
		else
			i++;
	}
	return (i);
}

void	expand_var(t_input_info *infos, int i, int quote, t_exitcode *exit_code)
{
	char	*temp_input;
    char    env_input[20];
    int     j;

    j = 0;
    i++;
	if (infos->input[i] == '?')
	{
		env_input[0] = '?';
		env_input[1] = '\0';
		temp_input = ft_itoa(exit_code->last_cmd);
		resize_and_copy(infos, i+1, 1, temp_input);
		return ;
	}
	else if(ft_isalnum(infos->input[i]) || infos->input[i] == '_')
	{
    	while (infos->input[i] && (ft_isalnum(infos->input[i]) || infos->input[i] == '_'))
   		{
			if (quote && infos->input[i] == '"')
				break ;
        	env_input[j++] = infos->input[i++];
    	}
    	env_input[j] = '\0';
		temp_input = getenv(env_input);
	}
	else
		return ;
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
        buffer[k++] = infos->input[x++];
    x = 0;
    while (x < ft_strlen(temp_input))
        buffer[k++] = temp_input[x++];
    while (infos->input[i])
        buffer[k++] = infos->input[i++];
    buffer[k] = '\0';
    //free(infos->input);
    infos->input = buffer;
}
