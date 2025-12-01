/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_in_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:43:37 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/27 16:47:24 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

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
	char	*tmp;
	char	quote;
	int		open;

	open = 0;
	tmp = ft_malloc((len + 1) * sizeof(char), 0);
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
	return (tmp);
}

char	*get_env_by_name(char *var_temp, t_env *env)
{
	char	*tmp;
	int		i;
	int		k;
	int		j;

	i = 0;
	tmp = getenv(var_temp);
	if (tmp)
		return (tmp);
	while (env->global[i])
	{
		if (ft_strncmp(var_temp, env->global[i],
				ft_strlen_var(env->global[i])) == 0
			&& ft_strncmp(var_temp, env->global[i],
				ft_strlen_var(var_temp)) == 0)
		{
			tmp = get_var_value(0, 0, i, env);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
