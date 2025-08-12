/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:53:10 by mleschev          #+#    #+#             */
/*   Updated: 2025/08/12 21:01:41 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_PARSE_H
# define LIB_PARSE_H

# ifndef PROMPT_LINE
# define PROMPT_LINE ".>"
# endif

typedef struct t_input
{
	char	*commands;
	char	**arguments;
	char	*operators;
	int		nbr_commands;
	int		nbr_arguments;
	int		nbr_operators;
} t_input;

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

// parse_input.c
t_input *manage_input(const char *str);
void	init_input(t_input *input, const char *str);
int	check_operator_in_str(const char *str);


# endif
