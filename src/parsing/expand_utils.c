/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:13:21 by jmalaval          #+#    #+#             */
/*   Updated: 2025/11/28 15:17:58 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lib_parse.h"

void	erase_in_str(t_input_info *infos, int i)
{
	char	*buffer;
	int		j;

	j = 0;
	buffer = ft_malloc(sizeof(char) * (ft_strlen(infos->input) + 1), 0);
	if (!buffer)
		return ;
	while (j < i)
	{
		buffer[j] = infos->input[j];
		j++;
	}
	while (infos->input[i])
	{
		buffer[j] = infos->input[i + 1];
		j++;
		i++;
	}
	buffer[j] = '\0';
	infos->input = buffer;
}

void	resize_and_copy(t_input_info *infos, int i, int j, char *temp_input)
{
	char	*buffer;
	int		k;
	int		x;
	int		length;

	x = 0;
	k = 0;
	length = ft_strlen(infos->input) - j + ft_strlen(temp_input) + 1;
	buffer = ft_malloc(sizeof(char) * length, 0);
	while (k < i - j - 1)
		buffer[k++] = infos->input[x++];
	x = 0;
	while (x < ft_strlen(temp_input))
		buffer[k++] = temp_input[x++];
	while (infos->input[i])
		buffer[k++] = infos->input[i++];
	buffer[k] = '\0';
	infos->input = buffer;
}
