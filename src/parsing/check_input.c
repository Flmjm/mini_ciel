/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 08:51:44 by mleschev          #+#    #+#             */
/*   Updated: 2025/11/19 16:37:38 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

void	is_complete(t_input_info *infos)
{
	int		i;

	i = 0;
	while (infos->input[i])
	{
		if (infos->input[i] == '\'')
			i = next_simple_quote(infos, i, TRUE);
		else if (infos->input[i] == '"')
			i = next_double_quote(infos, i, TRUE);
		else if (infos->input[i] == '\\' && infos->input[i + 1] == '\0')
		{
			infos->input[i] = '\n';
			recall_readline(infos);
		}
		else if (infos->input[i] == '\\')
		{
			quote_next_char(infos, i);
			i += 2;
		}
		i++;
	}
	if (i > 0 && infos->input[i - 1] == '\n')
		infos->input[i - 1] = '\0';
}

void	recall_readline(t_input_info *infos)
{
	char	*buffer;
	char	*temp_input;
	int		buffer_len;
	int		temp_len;
	int		total_len;

	temp_input = readline(">");
	if (!temp_input)
		return ;
	buffer_len = ft_strlen(infos->input);
	temp_len = ft_strlen(temp_input);
	total_len = buffer_len + temp_len + 2;
	buffer = ft_malloc(sizeof(char) * (buffer_len + 1), 0);
	ft_strlcpy(buffer, infos->input, buffer_len + 1);
	infos->input = ft_malloc(sizeof(char) * total_len, 0);
	ft_strlcpy(infos->input, buffer, total_len);
	if (temp_len > 0)
		ft_strlcat(infos->input, temp_input, total_len);
	ft_strlcat(infos->input, "\n", total_len);
}

int	next_simple_quote(t_input_info *infos, int i, int init)
{
	i = i + 1;
	while (infos->input[i] != '\'')
	{
		if (init == TRUE)
		{
			while (infos->input[i] == '\0')
			{
				replace_azt(infos, i);
				recall_readline(infos);
			}
		}
		if (infos->input[i] == '\'')
			return (i);
		if (!infos->input[i])
			break ;
		i++;
	}
	return (i);
}

void	replace_azt(t_input_info *info, int i)
{
	char	*temp;

	temp = ft_malloc(sizeof(char) * (ft_strlen(info->input) + 2), 0);
	ft_strlcpy(temp, info->input, ft_strlen(info->input) + 1);
	temp[i] = '\n';
	temp[i + 1] = '\0';
	info->input = temp;
}

int	next_double_quote(t_input_info *infos, int i, int init)
{
	i = i + 1;
	while (infos->input[i] != '"')
	{
		if (init == TRUE)
		{
			while (infos->input[i] == '\0')
				replace_and_recall(infos, i);
		}
		if (infos->input[i] == '"')
			return (i);
		else if (infos->input[i] == '\\')
		{
			if (infos->input[i + 1] == '\\' || infos->input[i + 1] == '"'
				|| infos->input[i + 1] == '`')
			{
				quote_next_char(infos, i);
				i += 2;
			}
			else if (infos->input[i + 1] == '$')
				i += 2;
		}
		i++;
	}
	return (i);
}
