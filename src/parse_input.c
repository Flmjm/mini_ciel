/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/13 15:58:28 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

t_input_info *manage_input(const char *str) //test
{
	t_input_info	*input;

	input = malloc(sizeof(t_input_info));
	init_info(input, str);

	free(input);
	return (input);
}

// void	make_input_format(const char *str, t_input_info *info)
// {

// }

void	init_info(t_input_info *input, const char *str)
{
	int	i;

	i = 0;
	input->nbr_arguments = 0;
	input->nbr_commands = 0;
	input->nbr_operators = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ' && check_operator_in_str(str[i]) == 0)
		{
			while (str[i] && str[i] != ' ' && check_operator_in_str(str[i]) == 0)
				i++;
			input->nbr_commands++;
		}
		while (str[i] && str[i] == ' ')
				i++;
		while (str[i] && str[i] != ' ' && check_operator_in_str(str[i]) == 0)
		{
			while (str[i] && str[i] != ' ' && check_operator_in_str(str[i]) == 0)
				i++;
			input->nbr_arguments++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		while (str[i] && str[i] != ' ' && check_operator_in_str(str[i]) == 1)
		{
			while (str[i] && str[i] != ' ' && check_operator_in_str(str[i]) == 1)
				i++;
			input->nbr_operators++;
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	printf("info.nbr_cmd: %d | info.nbr_ope: %d | info.nbr_arg: %d\n", input->nbr_commands, input->nbr_operators, input->nbr_arguments);
}


int	check_operator_in_str(const char str) //test
{
	if (str == ' ')
		return (0);
	else
	{
		if (str == '>'
			|| str == '<'
			|| str == ';'
			|| str == '|'
			|| str == '&'
			|| str == '\\'
			|| str == '*')
			return (1);
	}
	return (0);
}
