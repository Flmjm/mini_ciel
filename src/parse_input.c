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

t_input *manage_input(const char *str) //test
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	init_input(input, str);
	return (input);
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
