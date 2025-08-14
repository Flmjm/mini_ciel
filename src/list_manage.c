/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:14:22 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/15 00:25:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

void    init_lists(t_commands **head, t_input_info *info)
{
    int     i;
    int     is_cmd;
    char    *crnt_word;

    is_cmd = FALSE;
    i = 0;
    while (info->input[i] != NULL)
    {
        if (check_operator_in_str(info->input[i]) == 0 && is_cmd == FALSE)
        {
            
        }
        else if (is_redirection(info->input[i] > 0))
        {
            if (is_redirection(info->input[i]) == 1)
                add_node_infile();
            else if (is_redirection(info->input[i] == 2))
                add_node_outfile();
            is_cmd = FALSE;
        }
        i++;
    }
}

int     is_redirection(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] == '<'))
            return (1);
        if ((str[i] == '>'))
            return (2);
        i++;
    }
    return (0);
}

int	check_operator_in_str(const char *str)
{
	int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\\')
            return (1);
        else if (str[i] == '&')
            return (2);
        else if (str[i] == '|')
            return (3);
        else if (str[i] == ';')
            return (4);
        i++;
    }
	return (0);
}