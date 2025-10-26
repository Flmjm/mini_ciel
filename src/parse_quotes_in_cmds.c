/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_in_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:43:37 by jmalaval          #+#    #+#             */
/*   Updated: 2025/10/20 17:11:50 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_parse.h"


void	ft_check_quotes_struct_cmd(t_commands *commands)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (commands)
	{
		while (commands->argv[i])
		{
			commands->argv[i] = ft_check_quotes_argv(commands->argv[i], ft_strlen(commands->argv[i]) - 1);
			i++;
		}
		commands = commands->next;
	}
}

char *ft_check_quotes_argv(char *cmds, int len)
{
    int     j;
    int    k;
    char    *tmp;
    char    *res;

    j = 0;
    k = len;
    res = NULL;
    if (cmds[j] != '"' && cmds[j] != '\'')
        return(cmds);
    while (cmds[j] == cmds[0] && cmds[k] == cmds[0])
    {    
        j++;
        k--;
    }
    tmp = ft_substr(cmds, j, k - j + 1);
    if (j == len - k && j % 2 == 0)
    {
        res = ft_check_quotes_argv(tmp, ft_strlen(tmp) - 1);
        return (res);
    }
    return(tmp);
}
