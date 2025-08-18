/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/16 06:51:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_parse.h"

void *manage_input(char *str) //convertis l'input de readline en infos puis en **argv et en liste chainees
{
	t_input_info	*info;
	// t_commands		*head;
	
	info = malloc(sizeof(t_input_info));
	// head = malloc(sizeof(t_commands));
	init_info(info, str); //infos
	// init_input_format(info, str); //**argv
	// init_lists(&head, info);
	// int i = 0;
	// while (info->input[i] != NULL)
	// {
	// 	printf("|%d|%s|\n", i, info->input[i]);
	// 	i++;		
	// }
	printf("%s\n", str);
	printf("%d\n", ft_strlen(str));
	// printf("info.nbr_cmd: %d | info.nbr_ope: %d | info.nbr_arg: %d || args: %d\n", info->nbr_commands, info->nbr_operators, info->nbr_arguments, info->args);
	free (info);
}


void	init_info(t_input_info *infos, char *str)
{
	int	len;
	int	first_lttr;
	char *result;
	char *temp;
	
	first_lttr = FALSE;
	is_complete(str); // analyse et renvoi la chaine complete si elle ne l'etait pas
	
	
}

void	is_complete(char *str)
{
	int		i;
	char	*buffer;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '{' || str[i] == '(')
			find_end_operator(str, '}', ')', i);
		else if (str[i] == '\\' && str[i + 1] == '\0')
			recall_readline(str);
		i++;
	}

	
}

int	find_end_operator(char *str, char end, char end2, int i) // a refaire
{
	int		j;
	
	j = i + 1;
	while (j <= ft_strlen(str))
	{
		if (str[j] == '"')
		{
			while (++j <= ft_strlen(str))
			{
				printf("j:%d", j);
				if (str[j] == '"')
					break ;
				if (str[j] == '\0')
				{
					recall_readline(str);
					j = i + 1;
				}
			}
		}
		else if (str[j] == '\'')
		{
			while (j <= ft_strlen(str))
			{
				j++;
				if (str[j] == '\'')
					break ;
				else if (str[j] == '\0')
				{
					recall_readline(str);
					j = i + 1;
				}
			}
		}
		if (str[j] == '\0')
		{
			recall_readline(str);
			j = i + 1;
		}
		if (str[j] == end)
			break ;
		j++;
	}
	printf("j:%d\n", j);
	return (0);
}

void	recall_readline(char *str)
{
	char	*buffer;
	char	*temp_input;

	temp_input = readline(">");
	if (ft_strlen(temp_input) == 0)
		return ;
	buffer = malloc(sizeof(char) * ft_strlen(str));
	ft_strlcpy(buffer, str, ft_strlen(str) + 1);
	free(str);
	str = malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(temp_input) + 1));
	ft_strlcpy(str, buffer, (ft_strlen(buffer) + ft_strlen(temp_input)));
	free(buffer);
	ft_strlcat(str, temp_input, ft_strlen(str) + ft_strlen(temp_input) + 1);
	free(temp_input);
}