/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manu <manu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 01:48:37 by manu              #+#    #+#             */
/*   Updated: 2025/11/17 01:50:35 by manu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

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
