/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/12 21:03:48 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

char manage_input(const char *str) //test
{
	int	i;
	t_input	*input;

	input = malloc(sizeof(t_input));
	init_input(input, str);
	i = 0;
}

void	init_input(t_input *input, const char *str) //test
{
	int	i;
	int	cmd;
	int	arg;
	int	ope;

	cmd = 0;
	arg = 0;
	ope = 0;
	i = 0;
	input->arguments = "";
	input->arguments = "";
	input->operators = "";
	input->nbr_arguments = 0;
	input->arguments = 0;
	input->nbr_operators = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		while (str[i] != ' ')
		{
			input->commands[cmd] = str[i];
			i++;
		}
		cmd++;
		while (check_operator_in_str(str[i]) == 0)
		{

		}


	}
}

int	check_operator_in_str(const char *str) //test
{
	int	i;

	i = 0;
	if (str[i] == ' ')
		return (0);
	else
	{
		if (str[i] == '>'
			|| str[i] == '<'
			|| str[i] == ';'
			|| str[i] == '|'
			|| str[i] == '&'
			|| str[i] == '\\'
			|| str[i] == '*')
			return (1);
	}
	return (0);
}
