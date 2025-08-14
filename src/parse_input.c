/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/15 00:50:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

void *manage_input(char *str) //convertis l'input de readline en infos puis en **argv et en liste chainees
{
	t_input_info	*info;
	t_commands		*head;
	
	info = malloc(sizeof(t_input_info));
	head = malloc(sizeof(t_commands));
	init_info(info, str); //infos
	init_input_format(info, str); //**argv
	// init_lists(&head, info);
	int i = 0;
	while (info->input[i] != NULL)
	{
		printf("|%d|%s|\n", i, info->input[i]);
		i++;		
	}

	printf("info.nbr_cmd: %d | info.nbr_ope: %d | info.nbr_arg: %d || args: %d\n", info->nbr_commands, info->nbr_operators, info->nbr_arguments, info->args);
	free (info);
}

void	init_info(t_input_info *input, const char *str) //how much cmd, args and operators
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
		while (str[i] && str[i] != ' ' && check_operator_in_char(str[i]) == 0)
		{
			while (str[i] && str[i] != ' ' && check_operator_in_char(str[i]) == 0)
				i++;
			input->nbr_commands++;
		}
		while (str[i] && str[i] == ' ')
				i++;
		while (str[i] && str[i] != ' ' && check_operator_in_char(str[i]) == 0)
		{
			while (str[i] && str[i] != ' ' && check_operator_in_char(str[i]) == 0)
				i++;
			input->nbr_arguments++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		while (str[i] && str[i] != ' ' && check_operator_in_char(str[i]) == 1)
		{
			while (str[i] && str[i] != ' ' && check_operator_in_char(str[i]) == 1)
				i++;
			input->nbr_operators++;
			while (str[i] && str[i] == ' ')
				i++;
		}
	}
	input->args = input->nbr_arguments + input->nbr_commands + input->nbr_operators;
}

void	init_input_format(t_input_info *info, const char *input_str)
{
	int i;
	int	j;
	if (info->args < 1)
		return ;
	info->input = malloc(sizeof(char *) * (info->args + 1));
	if (!info->input)
		return ;
	trunc_spaces(info, input_str);
}

void trunc_spaces(t_input_info *info, const char *str)
{
    int i = 0;
	int j = 0; 
	int word_nbr = 0;
    int len;

    while (str[i])
    {
        while (str[i] == ' ')
            i++;
        if (!str[i])
            break;

        len = strlen_to_space(str + i);
        info->input[word_nbr] = malloc(sizeof(char) * (len + 1));
        if (!info->input[word_nbr])
            return;
        j = 0;
        while (str[i] && str[i] != ' ')
            info->input[word_nbr][j++] = str[i++];
        info->input[word_nbr][j] = '\0';

        word_nbr++;
    }
    info->input[word_nbr] = NULL;
}


int	check_operator_in_char(const char lttr) //test
{
	if (lttr == ' ')
		return (0);
	else
	{
		if (lttr == '>'
			|| lttr == '<'
			|| lttr == ';'
			|| lttr == '|'
			|| lttr == '&'
			|| lttr == '\\'
			|| lttr == '*')
			return (1);
	}
	return (0);
}

int	strlen_to_other_token(const char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if ((str[i] != ' ' 
			|| str[i] != '\\' 
			|| str[i] != ';' 
			|| str[i] != '|' 
			|| str[i] != '&'))
			return (i);
		i++;
	}
	return (i);
}