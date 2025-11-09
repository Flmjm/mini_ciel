/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:32:07 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/08 22:16:58 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_exec.h"

static int check_option_n(char *str)
{
    size_t i;
    
    i = 0;
    if (str[i] && str[i] == '-')
    {
        i++;
        while (str[i] && str[i] == 'n')
            i++;
        if (i == ft_strlen(str))
            return(1);
    }
    return (0);
}

int    ft_echo(char **cmd)
{
    int i;
    int no_new_line;
    int nb_args;

    i = 1;
    no_new_line = 0;
    nb_args = argc_of_argv(cmd) - 1;
    while (cmd[i] && check_option_n(cmd[i]) == 1)
    {
        no_new_line = 1;
        i++;
    }
    while(i <= nb_args)
    {
        ft_putstr_fd(cmd[i], 1);
        if (i < nb_args)
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (no_new_line == 0)
        write(1, "\n", 1);
    return (0);
}
