/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 01:48:37 by manu              #+#    #+#             */
/*   Updated: 2025/12/02 11:02:29 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

static void	clean_cmds(int i, t_commands *cmds);

void	quote_next_char(t_input_info *infos, int i)
{
	int		lenght;
	char	*buffer;
	int		j;

	j = i;
	lenght = ft_strlen(infos->input);
	buffer = ft_malloc(sizeof(char) * (lenght + 1), 0);
	ft_strlcpy(buffer, infos->input, j + 1);
	buffer[j] = '\'';
	j++;
	buffer[j] = infos->input[i + 1];
	i++;
	j++;
	buffer[j] = '\'';
	j++;
	while (j <= lenght)
	{
		buffer[j] = infos->input[i + 1];
		j++;
		i++;
	}
	buffer[j] = '\0';
	infos->input = buffer;
}

void	replace_and_recall(t_input_info *infos, int i)
{
	replace_azt(infos, i);
	recall_readline(infos);
}

void	clean_var(t_commands *cmds)
{
	int	i;

	i = 0;
	while (cmds->argv[i])
	{
		if (cmds->argv[i][0] == '$' && cmds->argv[i][1])
			clean_cmds(i, cmds);
		if (!cmds->argv[i])
			break ;
		i++;
	}
}

static void	clean_cmds(int i, t_commands *cmds)
{
	while (cmds->argv[i])
	{
		cmds->argv[i] = cmds->argv[i + 1];
		i++;
	}
}

char	*get_var_value(int k, int j, int i, t_env *env)
{
	char	*tmp;

	tmp = ft_malloc(sizeof(char) * (ft_strlen(env->global[i])
				+ 1), 0);
	if (env->global[i])
		j = ft_strlen_var(env->global[i]) + 1;
	else
		return (NULL);

	while (env->global[i][j])
	{
		tmp[k] = env->global[i][j];
		k++;
		j++;
	}
	tmp[k] = '\0';
	return (tmp);
}
