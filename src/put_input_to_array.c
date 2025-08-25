/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_input_to_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:16:36 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/25 22:00:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

char	**convert_input_to_array(t_input_info *infos)
{
	char **buffer;
	int	length;
	int	i;

	i = 0;
	infos->nbr_args = how_much_args(infos);
	buffer = malloc(sizeof(char *) * (infos->nbr_args + 1));
	while (i < how_much_args(infos))
	{
		length = strlen_of_args(infos, i);
		buffer[i] = malloc(sizeof(char) * (length + 1));
		copy_arg(infos, buffer[i], i);
		i++;
	}
	buffer[i] = NULL;
	return (buffer);
}

void	copy_arg(t_input_info *infos, char *buffer, int arg) //bug
{
	int	length;
	int i;
	int	current_arg;
	int j;
	int k;

	k = 0;
	j = 0;
	i = 0;
	length = 0;
	current_arg = 0;
	while (infos->input[i])
	{	
		while (infos->input[i] == ' ')
			i++;
		if (infos->input[i] && infos->input[i] != ' ')
		{
			if (current_arg == arg)
			{
				while (infos->input[i] && infos->input[i] != ' ')
				{
					if (infos->input[i] == '"')
					{	
						k = next_double_quote(infos, i, FALSE);
						i++;
						while (i < k)
						{
							buffer[j] = infos->input[i];
							i++;
							j++;
						}
					}
					else if (infos->input[i] == '\'')
					{	
						k = next_simple_quote(infos, i);
						i++;
						while (i < k)
						{
							buffer[j] = infos->input[i];
							i++;
							j++;
						}
					}
					else if (infos->input[i] && infos->input[i] != ' ')
					{	
						buffer[j] = infos->input[i];
						j++;
					}
					if (ft_strlen(infos->input) < i)
						break ;
					i++;
				}
				buffer[j] = '\0';
				return ;
			}
			while (infos->input[i] && infos->input[i] != ' ')
			{	
				if (infos->input[i] == '"')
					i = next_double_quote(infos, i, FALSE);
				else if (infos->input[i] == '\'')
					i = next_simple_quote(infos, i);
				i++;
			}
			current_arg++;
		}
	}
}
int		how_much_args(t_input_info *infos)
{
	int	result;
	int i;

	i = 0;
	result = 0;
	while (infos->input[i])
	{
		if (infos->input[i] == ' ')
		{
			while (infos->input[i] == ' ')
				i++;
		}
		if (infos->input[i] && infos->input[i] != ' ')
		{
			while (infos->input[i] && infos->input[i] != ' ')
			{	
				if (infos->input[i] == '"')
					i = next_double_quote(infos, i, FALSE);
				if (infos->input[i] == '\'')
					i = next_simple_quote(infos, i);
				i++;
			}
			result++;
		}
	}
	return (result);
}