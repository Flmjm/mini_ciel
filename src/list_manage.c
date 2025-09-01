/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:14:22 by mleschev          #+#    #+#             */
/*   Updated: 2025/09/01 13:03:16 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

void    init_lists(t_commands **head, t_input_info *info)
{
    int     i;
    int     new_cmd;

    new_cmd = TRUE;
    i = 0;
    while (info->argv[i] != NULL)
    {
        if (is_redirection(info->argv[i]) == 0 && new_cmd == TRUE)
        {
            add_node_cmd();
            new_cmd = FALSE;
        }
        else if (is_redirection(info->argv[i]) == 0 && new_cmd == FALSE)
            add_node_arg();
        else if (is_redirection(info->argv[i]) == 1)
            add_node_infile();
        else if (is_redirection(info->argv[i]) == 2)
            add_node_outfile();
        else if (is_operator())
        {

            new_cmd = TRUE;
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
        if (str[i] == '&')
            return (2);
        else if (str[i] == '|')
            return (3);
        else if (str[i] == ';')
            return (4);
        i++;
    }
	return (0);
}

int is_operator(char *str)
{
    int i;

    i = 0;
    while ()
}
