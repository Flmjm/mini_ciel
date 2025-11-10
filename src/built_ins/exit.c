/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:24:33 by juliette-ma       #+#    #+#             */
/*   Updated: 2025/11/10 12:21:04 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"
#include "../../include/lib_exec.h"

static int check_arg(char *av)
{
    int i;

    i = 0;
    if (av[i] == '+' || av[i] == '-')
        i++;
    while (av[i])
    {
        if (!ft_isdigit(av[i]))
            return(1);
        i++;
    }
    return(0);
}

void clear_and_exit(int n)
{
    rl_clear_history();
	ft_malloc(0, 1);
	exit(n);
}

int	ft_exit(t_env *env, char **cmds, int nbr_return)
{
	int argc;

    if (!cmds)
        clear_and_exit(nbr_return);
	argc = argc_of_argv(cmds);
	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		clear_and_exit(1);
	}
	else if (argc == 2)
	{
		if (check_arg(cmds[1]))
        {
            ft_putstr_fd(cmds[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            clear_and_exit(2);
        }
        else
            clear_and_exit(ft_atoi(cmds[1]));
	}
    else
	    clear_and_exit(nbr_return);
}
