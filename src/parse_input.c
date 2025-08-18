/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:21:57 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/18 12:05:36 by mleschev         ###   ########.fr       */
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
	int		d_quote;
	int		quote;
	char	*buffer;


	if (have_quote(str))
	{
		d_quote = 1;
		while (d_quote % 2 != 0 || quote % 2 != 0)
		{
			d_quote = 0;
			quote = 0;
			i = 0;
			while (str[i])
			{
				if (str[i] == '"')
					d_quote++;
				else if (str[i] == '\'')
					quote++;
				i++;
			}
			if ((d_quote % 2 != 0 || quote % 2 != 0))
				recall_readline(str);
		}
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '\0')
			recall_readline(str);
		else if (str[i] == '\\' && str[i + 1] != '\0')
			replace_backslash(str);

		i++;
	}


}

int	find_end_operator(char *str, char end, char end2, int i) // a refaire
{
	int	j;

	j = i + 1;
	while (j <= ft_strlen(str))
	{
		if (str[j] == end || str[j] == end2)
			return (0);

		else if (str[j] == '\0')
			recall_readline(str);
	}
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

int		have_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	replace_backslash(char *str)
{
	int	i;
	int	lenght;

	i = 0;
	lenght = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '\\')
			lenght += 2;
		i++;
	}
}
