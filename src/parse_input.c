/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/14 16:28:43 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

t_input_info *manage_input(const char *str) //test
{
	t_input_info	*info;

	info = malloc(sizeof(t_input_info));
	init_info(info, str);
	init_format(info);


	printf("info.nbr_cmd: %d | info.nbr_ope: %d | info.nbr_arg: %d\n", info->nbr_commands, info->nbr_operators, info->nbr_arguments);

	free(info);
	return (info);
}

void	init_format(t_input_info *info)
{
	
}

void	init_info(t_input_info *input, const char *str) //how much cmd, args and operators
{
	int	i;
	int	j;
	int	ltr;

	ltr = 0;
	j = 0;
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
