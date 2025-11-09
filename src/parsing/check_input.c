/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:51:44 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/09 01:08:39 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

void	is_complete(t_input_info *infos) // prend en charge \ ' " pour l'instant
{
	int i;

	i = 0;
	while (infos->input[i])
	{
		if (infos->input[i] == '\'')
			i = next_simple_quote(infos, i, TRUE);
		else if (infos->input[i] == '"')
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
	buffer = ft_malloc(sizeof(char) * (ft_strlen(infos->input) + 1), 0);
	ft_strlcpy(buffer, infos->input, ft_strlen(infos->input) + 1);
	infos->input = ft_malloc(sizeof(char) * (ft_strlen(buffer)
				+ ft_strlen(temp_input) + 1), 0);
	ft_strlcpy(infos->input, buffer, (ft_strlen(buffer) + 1
			+ ft_strlen(temp_input)));
	ft_strlcat(infos->input, temp_input, ft_strlen(infos->input)
		+ ft_strlen(temp_input) + 1);
}

int	next_simple_quote(t_input_info *infos, int i, int init)
{
	i = i + 1;
	while (infos->input[i] && infos->input[i] != '\'')
	{
		if (init == TRUE && infos->input[i] == '\0')
		{
			replace_azt(infos, i);
			recall_readline(infos);
			while (infos->input[i] == '\0')
			{
				replace_azt(infos, i);
				recall_readline(infos);
			}
		}
		i++;
	}
	return (i);
}

void	replace_azt(t_input_info *info, int i)
{
	char	*temp;

	temp = ft_malloc(sizeof(char) * (ft_strlen(info->input) + 2), 0);
	ft_strlcpy(temp, info->input, ft_strlen(info->input) + 1);
	temp[i] = '\n';
	temp[i + 1] = '\0';
	info->input = temp;
}

int	next_double_quote(t_input_info *infos, int i, int init)
		// bug sur input: "\"
{
	i = i + 1;
	while (infos->input[i] && infos->input[i] != '"')
	{
		if (init == TRUE && infos->input[i] == '\0')
		{
			while (infos->input[i] == '\0')
			{
				replace_azt(infos, i);
				recall_readline(infos);
			}
		}
		if (infos->input[i] == '\\' && infos->input[i + 1])
		{
			if (infos->input[i + 1] == '\\' || infos->input[i + 1] == '"'
				|| infos->input[i + 1] == '`')
			{
				quote_next_char(infos, i);
				i += 2;
			}
			else if (infos->input[i + 1] == '$')
				i += 2;
			else
				i++;
		}
		else
			i++;
	}
	return (i);
}

void	quote_next_char(t_input_info *infos, int i)
{
	int		lenght;
	char	*buffer;
	int		j;

	// int i_return ;
	// i_return (= i + 2);
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
	// free(infos->input);
	infos->input = buffer;
}
