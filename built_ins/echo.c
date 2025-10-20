/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:32:07 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/10/20 23:52:53 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/pipex_bonus.h"
// a modifier pour le .h du projet


int check_option_n(char *str)
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

int    ft_echo(char **cmd) //(char **cmd, int fd)
{
    int i;
    int no_new_line;

    i = 1;
    no_new_line = 0;
    while (cmd[i] && check_option_n(cmd[i]) == 1)
    {
        no_new_line = 1;
        i++;
    }
    while(cmd[i])
    {
        ft_putstr_fd(cmd[i], 1);
        if (cmd[i+1] && cmd[i+1][0] != '\0')
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (no_new_line == 0)
        write(1, "\n", 1);
    return (0);
}

//gestion erreurs

// echo -n = echo -nnnnnn = echo -n -n -n ... retire le \n
// est ce qu'on gère le fd ici ou ailleurs ?
// ex echo hello > fichier --> ft_putstr_fd("hello", fichier)

// int main(int ac, char **av)
// {
//     if (ac > 1)
//         ft_echo(av+1);
// }
