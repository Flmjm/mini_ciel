/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_in_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:43:37 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/03 18:45:44 by jmalaval         ###   ########.fr       */
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
		while (commands && commands->argv[i])
		{
			commands->argv[i] = ft_check_quotes_argv(commands->argv[i],
					ft_strlen(commands->argv[i]), 0, 0);
			i++;
		}
		commands = commands->next;
		i = 0;
	}
}

char	*ft_check_quotes_argv(char *cmds, int len, int i, int j)
{
	char *tmp;
	char	quote;
	int	open;

	open = 0;
	tmp = ft_malloc((len +1) * sizeof(char), 0);
	while (cmds[i])
	{
		if ((cmds[i] == '"' || cmds[i] == '\'') && open == 0)
		{
			open = 1;
			quote = cmds[i];
			i++;
			while (cmds[i] && cmds[i] != quote)
				tmp[j++] = cmds[i++];
			open = 0;
			i++;
		}
		else
			tmp[j++] = cmds[i++];
	}
	tmp[j] = '\0';
	return(tmp);
}
