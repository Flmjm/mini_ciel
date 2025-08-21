/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/20 10:34:28 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

void *manage_input(char *str) //gere l'input de readline et la passe en **argv et en liste chainees
{
	t_input_info *infos;
	
	infos = malloc(sizeof(t_input_info));
	infos->input = str;
	is_complete(infos);
	convert_input_to_array(infos);
	printf("input: %s\n", infos->input);
	printf("lenght input: %d\n", ft_strlen(infos->input));
	// printf("info.nbr_cmd: %d | info.nbr_ope: %d | info.nbr_arg: %d || args: %d\n", info->nbr_commands, info->nbr_operators, info->nbr_arguments, info->args);
	
	
	free(infos);
}

int		how_much_args(t_input_info *infos, int i)
{
	int	result;

	result = 0;
	while (infos->input[i])
	{
		if (infos->input[i] == '"')
		{
			result++;
			i = next_double_quote(infos, i);
		}
		else if (infos->input[i] == '\'')
		{
			result++;
			i = next_simple_quote(infos, i);
		}
		else if (infos->input[i] != ' ')
		{
				result++;
				while (infos->input[i] && infos->input[i] != ' ')
					i++;
		}
		i++;
	}
	return (result);
}

void	convert_input_to_array(t_input_info *infos)
{
	char **buffer;
	int	length;
	int	i;

	i = 0;
	length = how_much_args(infos, 0);
	buffer = malloc(sizeof(char *) * (length + 1));
	buffer[length] = NULL;
	while (buffer[i])
	{
		length = strlen_of_args(infos, i, 0);
		printf("test strlen of args :%d    i:%d\n", length, i);
		i++;
	}
	
}
int		strlen_of_args(t_input_info *infos, int arg_search, int start)
{
	int	result;

	result = 0;
	while (infos->input[start])
	{
		if (infos->input[start] == '"')
		{
			result++;
			start = next_double_quote(infos, start);
		}
		else if (infos->input[start] == '\'')
		{
			result++;
			start = next_simple_quote(infos, start);
		}
		else if (infos->input[start] != ' ')
		{
				result++;
				if (result == arg_search)
				{	
					result = next_space(infos->input, start);
					return (result);
				}
				while (infos->input[start] && infos->input[start] != ' ')
					start++;
		}
		start++;
	}
	return (result);
}

int		next_space(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

void	clean_quote(t_input_info *infos)
{
	int	i;

	i = 0;
	while (infos->input[i])
	{
		if (infos->input[i] == '"')
			i = next_double_quote(infos, i);
		if (infos->input[i] == '\'')
		{
			erase_in_str(infos, i);
			i = 0;
		}
		i++;
	}
}

void	erase_in_str(t_input_info *infos, int i)
{
	char *buffer;
	int	j;
	j = 0;

	buffer = malloc(sizeof(char) * (ft_strlen(infos->input)));
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
	free(infos->input);
	infos->input = buffer;
}
