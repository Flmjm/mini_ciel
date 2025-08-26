/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/26 22:11:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

void *manage_input(char *str) //verifie l'input de readline et la passe en **argv et en liste chainees
{
	t_input_info *infos;
	
	infos = malloc(sizeof(t_input_info));
	infos->input = str;
	is_complete(infos);
	add_history(infos->input);
	printf("Clean Input:"RED"%s\n"RESET"HMA:"RED"%d\n\n"RESET, infos->input, how_much_args(infos));
	replace_var_input(infos);
	infos->argv = convert_input_to_array(infos);
	
	int i = 0;
	while (infos->argv[i])
	{
		printf("%d|%s|\n",i, infos->argv[i]);
		i++;
	}

	// convert_input_to_array(infos);
	// printf("input: %s\n", infos->input);
	// printf("lenght input: %d\n", ft_strlen(infos->input));
	// printf("info.nbr_cmd: %d | info.nbr_ope: %d | info.nbr_arg: %d || args: %d\n", info->nbr_commands, info->nbr_operators, info->nbr_arguments, info->args);
	
	
	free(infos);
}

void	replace_backslash_double_quote(t_input_info *infos)
{
	int i;

	i = 0;
	while (infos->input[i])
	{
		if (infos->input[i] == '"')
		{
			i++;
			while (infos->input[i] != '"')
			{
				if (infos->input[i] == '\\')
				{
					if (infos->input[i + 1] == '$')
						quote_next_char(infos, i);
					else if (infos->input[i + 1] == '\'')
						erase_in_str(infos, i);
				}
				i++;
			}
		}
		i++;
	}
	
}


int		strlen_of_args(t_input_info *infos, int arg)
{
	int	length;
	int i;
	int	current_arg;
	int j;

	j = 0;
	i = 0;
	length = 0;
	current_arg = 0;
	while (infos->input[i])
	{	
		while (infos->input[i] && infos->input[i] == ' ')
			i++;
		if (infos->input[i] && infos->input[i] != ' ')
		{
			if (current_arg == arg)
			{
				while (infos->input[i] && infos->input[i] != ' ')
				{
					j = 0;
					if (infos->input[i] == '"')
					{	
						j = next_double_quote(infos, i, FALSE);
						length = j - i + length - 1;
						i = j;
					}
					else if (infos->input[i] == '\'')
					{	
						j = next_simple_quote(infos, i);
						length = j - i + length - 1;
						i = j;
					}
					else
						length++;
					i++;
				}
				return (length);
			}
			while (infos->input[i] && infos->input[i] != ' ')
			{	
				if (infos->input[i] == '"')
					i = next_double_quote(infos, i, FALSE);
				else if (infos->input[i] == '\'')
					i = next_simple_quote(infos, i);
				i++;
			}
			current_arg++;
		}
	}
	return (length);
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
