/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:51:44 by mleschev          #+#    #+#             */
/*   Updated: 2025/10/07 15:03:03 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"

void	is_complete(t_input_info *infos) // prend en charge \ ' " pour l'instant
{
	int		i;

	i = 0;
	while (infos->input[i])
	{
		if (infos->input[i] == '\'')
			i = next_simple_quote(infos, i);
		if (infos->input[i] == '"')
			i = next_double_quote(infos, i, TRUE);
		else if (infos->input[i] == '\\' && infos->input[i + 1] == '\0')
		{
			infos->input[i] = '\n';
			recall_readline(infos);
		}
		else if (infos->input[i] == '\\')
		{
			quote_next_char(infos, i);
			i += 2;
		}
		i++;
	}


}

void	recall_readline(t_input_info *infos)
{
	char	*buffer;
	char	*temp_input;

	temp_input = readline(">");
	if (ft_strlen(temp_input) == 0)
		return ;
	buffer = ft_malloc(sizeof(char) * ft_strlen(infos->input), 0);
	ft_strlcpy(buffer, infos->input, ft_strlen(infos->input) + 1);
	//free(infos->input);
	infos->input = ft_malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(temp_input) + 1), 0);
	ft_strlcpy(infos->input, buffer, (ft_strlen(buffer) + ft_strlen(temp_input)));
	//free(buffer);
	ft_strlcat(infos->input, temp_input, ft_strlen(infos->input) + ft_strlen(temp_input) + 1);
	//free(temp_input);
}

int		next_simple_quote(t_input_info *infos, int i)
{
	i = i + 1;
	while (infos->input[i] != '\'')
	{
		while (infos->input[i] == '\0')
			recall_readline(infos);
		if (infos->input[i] == '\'')
			return (i);
		i++;
	}
	return (i);
}

int		next_double_quote(t_input_info *infos, int i, int init) // bug sur input: "\"
{
	i = i + 1;
	while (infos->input[i] != '"')
	{
		if (init == TRUE)
		{
			while (infos->input[i] == '\0')
				recall_readline(infos);
		}
		if (infos->input[i] == '"')
			return (i);
		else if (infos->input[i] == '\\')
		{
			if (infos->input[i + 1] == '\\' || infos->input[i + 1] == '"' || infos->input[i + 1] == '`')
			{
				quote_next_char(infos, i);
				i += 2;
			}
			else if (infos->input[i + 1] == '$')
				i += 2;
		}
		// backquote a rajouter : `
		i++;
	}
	return (i);
}

void	quote_next_char(t_input_info *infos, int i)
{
	int	lenght;
	char *buffer;
	int	j;
	//int i_return;

	//i_return = i + 2;
	j = i;
	lenght = ft_strlen(infos->input);
	buffer = ft_malloc(sizeof(char) * (lenght + 1), 0);
	ft_strlcpy(buffer, infos->input, j + 1);
	buffer[j] = '\'';
	j++;
	buffer[j] = infos->input[i + 1];
	i++;
	j++;
	buffer[j] = '\'';
	j++;
	while (j <= lenght)
	{
		buffer[j] = infos->input[i + 1];
		j++;
		i++;
	}
	buffer[j] = '\0';
	//free(infos->input);
	infos->input = buffer;
}
